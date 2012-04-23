/* 
 * File:   ECGSignal.h
 * Author: tomko
 *
 * Created on 21 kwiecień 2012, 12:18
 */

#ifndef ECGSIGNAL_H
#define	ECGSIGNAL_H

#include <mutex>
#include <list>
#include <vector>
#include <ctime>

template <class T> class ECGSignal
{
public:

  typedef std::list<T> data_t;
  typedef typename data_t::iterator it_data_t;
  typedef std::vector<data_t> vector_data_t;
  typedef typename vector_data_t::iterator it_vector_data_t;
  typedef std::vector<it_data_t> vector_it_data_t;

  /**
   * Konstruktor parametryczny z parametrem określającym liczbę przechowywanych sygnałów.
   * @param n Liczba przechowywanych sygnałów.
   */
  ECGSignal(int n) : data_signal(n), outs(n)
  {
    outs_count = 0;
    this->n = n;
    recording = false;
  }
  ECGSignal(const ECGSignal& orig) = delete;

  virtual ~ECGSignal()
  {
    for (auto s : data_signal)
    {
      s.clear();
    }
    data_signal.clear();
    outs.clear();
  }

  /**
   * Funkcja otwierąca dane do odczytu. Odczyt zaczyna się w ostatnio dodanym elemencie sygnału.
   * @return Uchwyt do danych.
   */
  int readOpen()
  {
    mx.lock();
    //zapisanie iteratora do data_t
    outs.push_back(--(data_signal.end()));
    mx.unlock();
    return outs_count++;
  }

  /**
   * Funkcja zamykająca dane do odczytu.
   * @param handle Uchwyt do danych.
   */
  void closeOpen(int handle)
  {
    //po zakonczeniu odczytu ustawiamy iterator na end
    outs[handle] == data_signal.end();
  }

  /**
   * Funkcja zapisująca nową porcję danych.
   * @param begin Iterator do pierwszego elementu porcji danych.
   * @param end Iterator do pierwszego za ostatnim elementem porcji danych.
   */
  template <class InputIterator> void store(InputIterator begin, InputIterator end)
  {
    mx.lock();
    for (it_vector_data_t it = data_signal.begin(); begin != end; ++it, ++begin)
    {
      it->push_back(*begin);
    }
    mx.unlock();
  }

  /**
   * Funkcja zwracająca iteratory do początku i końca danych (ostatni element też jest elementem danych).
   * @param handle Uchwyt do danych otrzymany z funkcji readOpen.
   * @param start Iterator do pierwszego elementu nowych danych.
   * @param end Iterator do ostaniego elementu nowych danych.
   * @return true jeśli są nowe dane, false w przeciwnym wypadku.
   */
  bool readData(int handle, it_data_t & start, it_data_t & end)
  {
    bool ret = false;
    if (outs[handle] == data_signal.end()) //uchwyt jest nieprawidłowy
    {
      return ret;
    }
    //badanie czy się przesunęło
    it_data_t last_it = outs[handle];
    mx.lock();
    if (last_it != --(data_signal.end()))
    {
      start = last_it;
      outs[handle] = end = --(data_signal.end());
      ret = true;
    }
    mx.unlock();
    return ret;
  }
  /**
   * Funkcja rozpoczynająca możliwość zapisu.
   */
  void startRecording()
  {
    recording = true;
    start = std::time(NULL);
  }
  /**
   * Funkcja kończąca zapis.
   */
  void stopRecording()
  {
    recording = false;
    stop = std::time(NULL);
  }
  /**
   * Funkcja zwracająca iteratory do początku i puerwszego elementu za ostatnim w sytuacji, gdy zapis jest skończony.
   * @param start Iterator do pierwszego elementu.
   * @param end Iterator do pierszego za ostatnim elementu.
   * @return true jeśli zapis jest skończony, false w przeciwnym wyapdku.
   */
  bool getAllData(it_vector_data_t & start, it_vector_data_t & end)
  {
    if (recording)
    {
      return false;
    }
    start = data_signal.begin();
    end = data_signal.end();
    return true;
  }

  /**
   * Funkcja zwracająca ilość przechowywanych danych.
   * @return ilość przechowywanych danych.
   */
  int getSize()
  {
   return data_signal.size() * data_signal[0].size();
  }
private:
  //mutex
  std::mutex mx;
  //dane
  vector_data_t data_signal;
  //iteratory dla modułów odczytujących
  vector_it_data_t outs;
  //liczba modułów odczytujących
  int outs_count;
  //liczba przechowywanych sygnałow
  int n;
  //kontrola czasu zapisu
  std::time_t start, stop;
  bool recording;
};

#endif	/* ECGSIGNAL_H */


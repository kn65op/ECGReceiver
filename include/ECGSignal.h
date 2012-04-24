/* 
 * File:   ECGSignal.h
 * Author: tomko
 *
 * Created on 21 kwiecień 2012, 12:18
 */

#ifndef ECGSIGNAL_H
#define	ECGSIGNAL_H

#include <mutex>
#include <atomic>
#include <list>
#include <vector>
#include <ctime>

//TODO usunąć
#include <iostream>

template <class T> class ECGSignal
{
public:

  typedef std::list<T> data_t;
  typedef typename data_t::iterator it_data_t;
  typedef std::vector<data_t> vector_data_t;
  typedef typename vector_data_t::iterator it_vector_data_t;
  typedef std::vector<it_data_t> vector_it_data_t;
  typedef std::vector<vector_it_data_t> outs_t;

  /**
   * Konstruktor parametryczny z parametrem określającym liczbę przechowywanych sygnałów.
   * @param n Liczba przechowywanych sygnałów.
   */
  ECGSignal(int n) : data_signal(n)
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
   * Funkcja otwierąca dane do odczytu. Odczyt zaczyna się w ostatnio dodanym elemencie sygnału. Jeśli sygnał nie jest jeszcze zapisywany to zwracane jest -1.
   * @return Uchwyt do danych lub -1 w przypadku błędu.
   */
  int readOpen()
  {
    if (!recording)
    {
      return -1;
    }
    mx.lock();
    //zapisanie iteratora do data_t
    int i = 0;
    int handle = outs_count;
    outs.push_back(vector_it_data_t(n));
    for (auto & o : outs[handle])
    {
      o = (--(data_signal[i++].end()));
    }
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
  template <class InputIterator> void store(InputIterator & begin, InputIterator & end)
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
   *
  bool readData(int handle, vector_data_t & res)
  {
    bool ret = false;
    if (outs[handle][0] == data_signal[0].end()) //uchwyt jest nieprawidłowy
    {
      return ret;
    }
    //badanie czy się przesunęło
    it_data_t last_it = outs[handle][0];
    mx.lock();
    while (outs[handle][0] != data_signal[0].end())
    {
      for (int i = 0; i < 3; i++)
      {
	std::cout << outs.size() << " " << outs[handle].size() << "\n";
        res[i].push_back(*(outs[handle][i]++));
      }
    }
    for (int i = 0; i < n; i++)
    {
      outs[handle][i] = --data_signal[i].end();
    }
    ret = true;
    mx.unlock();
    return ret;
  }
*/
  /**
   * Funkcja zwracająca iteratory do początku i końca danych (ostatni element też jest elementem danych).
   * @param handle Uchwyt do danych otrzymany z funkcji readOpen.
   * @param start Iterator do pierwszego elementu nowych danych.
   * @param end Iterator do ostaniego elementu nowych danych.
   * @return true jeśli są nowe dane, false w przeciwnym wypadku.
   */
  bool readData(int handle, vector_it_data_t & start, vector_it_data_t & end)
  {
    bool ret = false;
    if (outs[handle][0] == data_signal[0].end()) //uchwyt jest nieprawidłowy
    {
      return ret;
    }
    //badanie czy się przesunęło
    it_data_t last_it = outs[handle][0];
    mx.lock();
    if (last_it != --(data_signal[0].end()))
    {
      for (int i = 0; i < n; i++)
      {
        start[i] = outs[handle][i];
        end[i] = --(data_signal[i].end());
        outs[handle][i] = --data_signal[i].end();
      }
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
  outs_t outs;
  //liczba modułów odczytujących
  int outs_count;
  //liczba przechowywanych sygnałow
  int n;
  //kontrola czasu zapisu
  std::time_t start, stop;
  std::atomic<bool> recording;
};

#endif	/* ECGSIGNAL_H */


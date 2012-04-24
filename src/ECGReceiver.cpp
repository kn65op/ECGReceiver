/* 
 * File:   ECGReceiver.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 19:41
 */

#include "../include/ECGReceiver.h"

#include "../include/DeviceSelector.h"

#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sys/stat.h>

#include "../include/FakeDevice.h"

//TODO usunąć
#include <iostream>
#include <bits/stl_vector.h>
#include <bits/stl_bvector.h>
#include <errno.h>

ECGReceiver::ECGReceiver()
{
  set_title("ECGReceiver");
  set_size_request(200, 200);

  //przycik wyboru device
  select_device.set_label("Wyszukaj urządzenie");
  select_device.signal_clicked().connect(sigc::mem_fun(*this, &ECGReceiver::on_select_device_clicked));

  //startstop
  start_stop.set_label("Start");
  start_stop.set_sensitive(false);
  start_stop.signal_clicked().connect(sigc::mem_fun(*this, &ECGReceiver::on_start_stop_clicked));
  recording = false;

  //device_info
  name_text.set_label("Nazwa: ");
  MAC_text.set_label("MAC: ");

  //umieszczenie elementów
  add(main_box);
  main_box.pack_end(buttons_box);
  buttons_box.pack_start(select_device);
  buttons_box.pack_end(start_stop);
  main_box.pack_end(device_description_box);
  device_description_box.pack_start(name_box);
  device_description_box.pack_end(MAC_box);
  name_box.pack_start(name_text);
  name_box.pack_end(name);
  MAC_box.pack_start(MAC_text);
  MAC_box.pack_end(MAC);

  //Tworzenie menu
  ref_actiongroup = Gtk::ActionGroup::create();

  //file menu
  ref_actiongroup->add(Gtk::Action::create("LoadDevice", Gtk::Stock::OPEN, "_Otwórz"), sigc::mem_fun(*this, &ECGReceiver::openDeviceFromFile));
  ref_actiongroup->add(Gtk::Action::create("SaveDevice", Gtk::Stock::SAVE, "Zapi_sz"), sigc::mem_fun(*this, &ECGReceiver::saveDeviceToFile));
  ref_actiongroup->add(Gtk::Action::create("FileMenu", "Plik"));

  //uimanager
  ref_uimanager = Gtk::UIManager::create();
  ref_uimanager->insert_action_group(ref_actiongroup);

  add_accel_group(ref_uimanager->get_accel_group());

  //layout
  Glib::ustring ui_info =
          "<ui>"
          "  <menubar name='MenuBar'>"
          "    <menu action='FileMenu'>"
          "       <menuitem action='LoadDevice'/>"
          "       <menuitem action='SaveDevice'/>"
          "    </menu>"
          "  </menubar>"
          "</ui>";

  try
  {
    ref_uimanager->add_ui_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    exit(123);
    //    std::cerr << "budowanie menu nie wyszło: " << ex.what();
  }

  //dodanie do widoku menu
  Gtk::Widget * menubar = ref_uimanager->get_widget("/MenuBar");
  if (menubar)
  {
    main_box.pack_start(*menubar, Gtk::PACK_SHRINK);
  }

  //wyświetlanie
  main_box.show_all_children(true);
  main_box.show();

  //zerowanie signal
  signal = 0;

  //zerowanie device
  device = 0;

  //zerowanie context
  context = 0;

  setDeviceInfo();
}

ECGReceiver::~ECGReceiver()
{
}

void ECGReceiver::on_select_device_clicked()
{
  DeviceSelector ds;
  if (ds.run() == Gtk::RESPONSE_OK)
  {
    device = ds.getDevice();
  }
  setDeviceInfo();
}

void ECGReceiver::setDeviceInfo()
{
  if (device) // jest jakieś urządzenie
  {
    name.set_label(device->getName());
    MAC.set_label(device->getMAC());
    start_stop.set_sensitive(true);
  }
  else
  {
    name.set_label("Brak urządzenia");
    MAC.set_label("Brak urządzenia");
    start_stop.set_sensitive(false);
  }
}

void ECGReceiver::openDeviceFromFile()
{
  //dialog
  Gtk::FileChooserDialog fcdialog("Wybierz plik do wczytania", Gtk::FILE_CHOOSER_ACTION_OPEN);
  fcdialog.set_transient_for(*this);

  Glib::RefPtr<Gtk::FileFilter> filter_bde = Gtk::FileFilter::create();
  filter_bde->set_name("Pliki device");
  filter_bde->add_pattern("*.bde");
  fcdialog.add_filter(filter_bde);

  //przyciski
  fcdialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  fcdialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  if (fcdialog.run() == Gtk::RESPONSE_OK)
  {
    //TODO FOR DEBUG ONLY
    std::string asd = fcdialog.get_filename();
    asd = asd.substr(asd.size() - 8);
    if (asd == "test.bde")
    {
      device = new FakeDevice();
    }
    //TODO FOR DEBUG ONLY

    std::ifstream file(fcdialog.get_filename(), std::ios::in);
    if (!device)
    {
      device = new Device();
    }
    file >> *device;
    file.close();
    setDeviceInfo();
  }
}

void ECGReceiver::saveDeviceToFile()
{
  if (!device)
  {
    Gtk::MessageDialog(*this, "Nie ma urządzenia do zapisania!").run();
    return;
  }
  //dialog
  Gtk::FileChooserDialog fcdialog("Wybierz plik do zapisu", Gtk::FILE_CHOOSER_ACTION_SAVE);
  fcdialog.set_transient_for(*this);

  Glib::RefPtr<Gtk::FileFilter> filter_bde = Gtk::FileFilter::create();
  filter_bde->set_name("Pliki device");
  filter_bde->add_pattern("*.bde");
  fcdialog.add_filter(filter_bde);

  //przyciski
  fcdialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  fcdialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  if (fcdialog.run() == Gtk::RESPONSE_OK)
  {
    std::string fn = fcdialog.get_filename();
    int s = fn.size();
    if (!(s > 3 && fn[--s] == 'e' && fn[--s] == 'd' && fn[--s] == 'b' && fn[--s] == '.'))
    {
      fn += ".bde";
    }
    std::ofstream file(fn, std::ios::out);
    file << *device;
    file.close();
  }
}

void ECGReceiver::on_start_stop_clicked()
{
  if (recording) //koniec nagrywania
  {
    start_stop.set_label("Start");
    recording = false;
    reader->join(); //czekanie na skończenie nagrywania 
    listen_to_server->join();
    device->stopConnection();
    signal->stopRecording();
    ECGSignal<u_int32_t>::it_vector_data_t begin, end;
    signal->getAllData(begin, end);
    if (signal)
    {
      delete signal;
      signal = 0;
    }
    //TODO dopisać zapis do bazy
    //zapis po http POST do serwera
  }
  else //początek nagrywania
  {
    signal = new ECGSignal<u_int32_t > (3);
    start_stop.set_label("Stop");
    recording = true;
    device->startConnection();
    signal->startRecording();
    reader = new std::thread(&ECGReceiver::getData, this);
    //TODO uruchomienie serwera oferującgo websockety
    mkfifo("/tmp/ECGFromServer", 0600);
    int pid = fork();
    if (!pid)
    { //dziecko
      std::cout << "FORK\n";
      std::cout << execlp("python", "python", "websocketServer.py", NULL) << "\n";
      std::cout << errno << "\n";
      std::cout << "FORK BAD\n";
      exit(-1);
    }
    std::cout << pid << "\n";
    //matka
    listen_to_server = new std::thread(&ECGReceiver::listenToServer, this);
  }
}

void ECGReceiver::getData()
{
  std::vector<u_int32_t> vals(3);
  device->sendChar('s'); //start
  bool rec = recording;
  while (rec)
  {
    for (auto &v : vals)
    {
      v = device->receiveUInt4();
      std::cout << "data: " << v << "\n";
    }
    std::vector<u_int32_t>::iterator beg = vals.begin();
    std::vector<u_int32_t>::iterator ed = vals.end();
    signal->store(beg, ed);
    std::cout << "getdata\n";
    rec = recording;
    sleep(1);
  }
  device->sendChar('s'); //stop
  std::cout << signal->getSize() << "\n";
}

void ECGReceiver::createServer()
{
}

void ECGReceiver::listenToServer()
{
  
  std::cout << "listen\n";
  bool rec = recording;
  ECGSignal<u_int32_t>::vector_it_data_t start(3), end(3);
  std::cout << "przygotowanie\n";
  int hand;
  while ((hand = signal->readOpen()) == -1)
  {
    std::cout << hand << "Waintin\n";
    sleep(1);
  }
  while (rec)
  {
    if (signal->readData(hand, start, end))
    {
      std::ofstream pipe("/tmp/ECGFromServer", std::ios::out);
      while (start[0] != end[0])
      {
        for (int i = 0; i < 3; i++) // start to wektor 3 iteratorów
        {
          pipe << *(start[i]) << "\n";
          //std::cout << *(start[i]) << " Listen\n";
          ++start[i];
        }
      }
      pipe.close();
    }
    /*    for (auto &a : start) // start to wektor 3 iteratorów
        {
          pipe << *a;
        }*/
  
  rec = recording;
}
unlink("/tmp/ECGFromServer");
   
/*  bool rec = recording;
  while (rec && )*/
}
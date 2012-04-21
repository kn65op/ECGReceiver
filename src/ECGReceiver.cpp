/* 
 * File:   ECGReceiver.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 19:41
 */

#include "../include/ECGReceiver.h"

#include "../include/DeviceSelector.h"

#include <fstream>

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

  //zerowanie device
  device = 0;

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
  if (recording) // nagrywanie
  {
    start_stop.set_label("Start");
    recording = false;
    //TODO dopisać
  }
  else //nie nagrywanie
  {
    start_stop.set_label("Stop");
    recording = true;
    //TODO dopisać
  }
}

void 
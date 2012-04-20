/* 
 * File:   ECGReceiver.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 19:41
 */

#include "../include/ECGReceiver.h"

#include "../include/DeviceSelector.h"

ECGReceiver::ECGReceiver()
{
  set_title("ECGReceiver");
  set_size_request(200, 200);
  
  //przycik wyboru device
  select_device.set_label("Wybierz urządzenie");
  select_device.signal_clicked().connect(sigc::mem_fun(*this, &ECGReceiver::on_select_device_clicked));

  //device_info
  name_text.set_label("Nazwa: ");
  MAC_text.set_label("MAC: ");
  
  //umieszczenie elementów
  add(main_box);
  main_box.pack_end(buttons_box);
  buttons_box.pack_start(select_device);
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
  catch(const Glib::Error& ex)
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
  }
  else
  {
    name.set_label("Brak urządzenia");
    MAC.set_label("Brak urządzenia");
  }
}

void ECGReceiver::openDeviceFromFile()
{
  //TODO otwieranie
}

void ECGReceiver::saveDeviceToFile() const
{
  //TODO zapis
}
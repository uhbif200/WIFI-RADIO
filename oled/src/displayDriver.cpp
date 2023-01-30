#include "displayDriver.h"


using namespace std;



//typedef int(Display::*fint_t)(vector<MenuItem*>& new_menu);         // указателт на методы
//typedef void(Display::*fint_text)(string text);
//typedef void(Display::*fint_play)();


MenuItem* parcerMenuFormer(vector<string> &strok){
  if(strok.size() == 2){
    SysOutFactory sys_out_factory;
    if(strok.at(0).size() > 19)
      strok.at(0) = strok.at(0).substr(0, 19);
      printf("%c             %c\n", strok.at(0), strok.at(0).substr(0, 15));
    return( sys_out_factory.createMenuItem(strok.at(0),&Display::play_radio, strok.at(1) ) );
  }
  else{
    return nullptr;
  }
}

vector<MenuItem*> radioParcer(string &inputFileName){
  ifstream fileIN;
  fileIN.open(inputFileName);
  if(!fileIN){
    cout <<"file isn't open" <<endl;
  }
  else{
    cout <<"file is open" << endl;
  }

  string current_string;
  vector<string>* str = new vector<string>();
  vector<MenuItem*> menu;

  while(fileIN.eof() != 1){
        getline(fileIN, current_string);
        if( current_string.size() <= 1 ){
            if(parcerMenuFormer(*str) != nullptr){
                menu.push_back( parcerMenuFormer(*str) );
            }
            str = new vector<string>();
        }
        else{
            str->push_back(current_string);
        }

  }
  fileIN.close();
  return menu;
}


void MenuItem::doStaff(Display* dis){

}

void MenuItemChanger::doStaff(Display* dis){
    (dis->*funct)(*arg);
}

void MenuItemSyOut::doStaff(Display* dis) {
    (dis->*funct)(arg);
}

void MenuItemPlay::doStaff(Display* dis){
    (dis->*funct)();
}

MenuItem* ChangerFactory::createMenuItem(string text, fint_t funct, vector<MenuItem*>* menu_ptr){
    MenuItemChanger* meme = new MenuItemChanger();
    meme->text = text;
    meme->funct = funct;
    meme->arg = menu_ptr;
    return meme;
}

MenuItem* SysOutFactory::createMenuItem(string text, fint_text funct, string out){
    MenuItemSyOut* meme = new MenuItemSyOut();
    meme->text = text;
    meme->funct = funct;
    meme->arg = out;
    return meme;
}

MenuItem* PlayFactory::createMenuItem(string text, fint_play funct){
    MenuItemPlay* meme = new MenuItemPlay();
    meme->text = text;
    meme->funct = funct;
    return meme;
}


Display::Display(){


    oledDriverInit();
    oledClear();
    printf("init succesful\n");

    string input_radio_file = "/root/c/oled/radio_parced.txt";

    oledSetColumnAddressing(0,128);

    ChangerFactory changer_factory;
    SysOutFactory sys_out_factory;
    PlayFactory play_factory;

    submenu_radio_urls.reserve(15);
    submenu_radio_urls = radioParcer(input_radio_file);
    submenu_radio_urls.emplace(submenu_radio_urls.begin(), changer_factory.createMenuItem("Radio:", &Display::change_menu, &submenu));
    submenu_radio_urls.push_back(changer_factory.createMenuItem("Back", &Display::change_menu, &submenu));


    MenuItemChanger* mem = new MenuItemChanger;
    mem->funct = &Display::change_menu;

    submenu.reserve(10);
    submenu.push_back(sys_out_factory.createMenuItem("Menu:",&Display::delai_cheta, "dasda"));
    submenu.push_back(changer_factory.createMenuItem("Source", &Display::change_menu, &submenu_radio_urls));
    submenu.push_back(changer_factory.createMenuItem("Equalizer", &Display::change_menu, &submenu_equalizer));
    submenu.push_back(changer_factory.createMenuItem("Settings", &Display::change_menu, &submenu_settings));
    submenu.push_back(changer_factory.createMenuItem("Alarm", &Display::change_menu, &submenu_alarm));
    submenu.push_back(changer_factory.createMenuItem("Hide", &Display::change_menu, &submenu));
    submenu.push_back(sys_out_factory.createMenuItem("Shutdown", &Display::delai_cheta, string("234234")));
    submenu.push_back(changer_factory.createMenuItem("Chto?", &Display::change_menu, nullptr));

    submenu_source.reserve(10);
    submenu_source.push_back(changer_factory.createMenuItem("Source:", &Display::change_menu, &submenu_source));
    submenu_source.push_back(play_factory.createMenuItem("PlayList", &Display::play));
    submenu_source.push_back(play_factory.createMenuItem("Dir", &Display::play));
    submenu_source.push_back(play_factory.createMenuItem("Other", &Display::play));
    submenu_source.push_back(changer_factory.createMenuItem("Back", &Display::change_menu, &submenu));

    submenu_equalizer.reserve(10);
    submenu_equalizer.push_back(changer_factory.createMenuItem("Equalizer:", &Display::change_menu, &submenu_equalizer));
    submenu_equalizer.push_back(changer_factory.createMenuItem("Rock", &Display::change_menu, &submenu_equalizer));
    submenu_equalizer.push_back(changer_factory.createMenuItem("Pop", &Display::change_menu, &submenu_equalizer));
    submenu_equalizer.push_back(changer_factory.createMenuItem("Classic", &Display::change_menu, &submenu_equalizer));
    submenu_equalizer.push_back(changer_factory.createMenuItem("Jaz", &Display::change_menu, &submenu_equalizer));
    submenu_equalizer.push_back(changer_factory.createMenuItem("Off", &Display::change_menu, &submenu_equalizer));
    submenu_equalizer.push_back(changer_factory.createMenuItem("Back", &Display::change_menu, &submenu));

    submenu_settings.reserve(10);
    submenu_settings.push_back(changer_factory.createMenuItem("Settings:", &Display::change_menu, &submenu_settings));
    submenu_settings.push_back(changer_factory.createMenuItem("Time", &Display::change_menu, &submenu_settings));
    submenu_settings.push_back(changer_factory.createMenuItem("Network", &Display::change_menu, &submenu_settings));
    submenu_settings.push_back(changer_factory.createMenuItem("Back",&Display::change_menu, &submenu));

    submenu_alarm.reserve(10);
    submenu_alarm.push_back(changer_factory.createMenuItem("Alarm:", &Display::change_menu, &submenu_alarm));
    submenu_alarm.push_back(changer_factory.createMenuItem("Alarm 1", &Display::change_menu, &submenu_alarm));
    submenu_alarm.push_back(changer_factory.createMenuItem("Alarm 2", &Display::change_menu, &submenu_alarm));
    submenu_alarm.push_back(changer_factory.createMenuItem("Alarm 3", &Display::change_menu, &submenu_alarm));
    submenu_alarm.push_back(changer_factory.createMenuItem("Back", &Display::change_menu, &submenu));

};

int Display::draw_current_menu(){


  string text_zero = current_menu->at(0)->text;
  draw_text(0, 0, text_zero);

  int i = this->selected;
  int j = this->prew_first_row;

  if(i < j){
    this->prew_first_row-- ;

  }else if(i >= (this->prew_first_row + this->display_size - 2)){
    this->prew_first_row++ ;
  }

  if(this->prew_first_row != j || this->prew_selected == this->selected ){
    for (int k = this->prew_first_row , iter = 1; iter < this->display_size; k++ , iter++){
      if(k < this->current_menu->size()){
        string text = current_menu->at(k)->text;
        if(k == this->selected){
            text.insert(0, 1, '>');
        }
        draw_text(0, iter, text);
      }else{
        string text = "               ";
        draw_text(0, iter, text);
      }
    }
  } else{
    int k = this->prew_first_row;



    string text = current_menu->at(this->selected)->text;
    text.insert(0, 1, '>');
    draw_text(0, this->selected - k + 1, text);

    text = current_menu->at(this->prew_selected)->text;
    draw_text(0, this->prew_selected - k + 1, text);


  }


}

int Display::clrscr(){
    oledClear();
}

int Display::draw_text(int x, int y, string &text, int font){
  oledSetCursorByPixel( y , x * 6 + 7 );

  char tex[30];
  strcpy(tex, text.c_str());
  int i = strlen(tex);

  if(i  < 20){
    for( ; i < 20; i++){
      strcat(tex," ");
    }
  }

  oledWrite(tex);
}

int Display::right(){
    if(this->selected < current_menu->size()-1)
    {
      this->prew_selected = this->selected;
      this->selected += 1;
    }
    draw_current_menu();
}

int Display::left(){
      if(this->selected > 1){
        this->prew_selected = this->selected;
        this->selected -= 1;
      }
    draw_current_menu();
}

int Display::key_pressed(){
    this->current_menu->at(selected)->doStaff(this);           // вызывает функцию из menuitem
}


void Display::pause_key_pressed(){
  switch (this->program_playing_now) {
    case nothing:
      if(this->last_radio_play != nullptr){
        this->last_radio_play->doStaff(this);
      }
      break;
    case mpg123:
      system("killall mpg123");
      this->program_playing_now = nothing;
      break;
    case aplay:
      system("aplay killall");
      break;
    case moc:
      system("aplay mocp");
      break;
  }
}


void Display::play(){
    cout <<"playing" <<endl;
    switch (this->program_playing_now) {
      case mpg123:
        system("killall mpg123");
        break;
      case aplay:
        system("aplay killall");
        break;
      case moc:
        system("aplay mocp");
        break;
      default:
        cout<<"nothing playing now" <<endl;
        break;
    }

    thread th( [](){
      system("mpg123 http://icecast.vgtrk.cdnvideo.ru/mayakfm_mp3_192kbps ");
    } );
    th.detach();
    this->program_playing_now = mpg123;

}

int Display::change_menu(vector<MenuItem*>& new_menu){

    if(&new_menu != nullptr){
        this->current_menu = &new_menu;
      }
    this->selected = 1;
    this->prew_selected = 1;
    this->prew_first_row = 1;
    this->clrscr();
    this->draw_current_menu();
}

void Display::delai_cheta(string text){          //в перспективе метод должен что-то делать
    draw_text(5,5,text);
}

void Display::play_radio(string text){          //запускает проигрывание радио

  switch (this->program_playing_now) {
    case mpg123:
      system("killall mpg123");
      break;
    case aplay:
      system("killall aplay");
      break;
    case moc:
      system("killall mocp");
      break;
    default:
      cout<<"nothing playing" <<endl;
      break;
  }

  text = string("mpg123 ") + text;


  thread th( [text](){
    system(text.c_str());
  } );
  th.detach();

  this->program_playing_now = mpg123;

  SysOutFactory sys_out_factory;
  this->last_radio_play = sys_out_factory.createMenuItem("lala", &Display::play_radio, text.substr(6, text.size()) );
}

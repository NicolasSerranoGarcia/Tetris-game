#include "constants.h"


const int SCREENWIDTH = 960;

const int SCREENHEIGHT = 1000;


const char * BESTPLAYSFILEPATH ="src/logs/bestPlays.txt";

const char * KEYBINDSFILEPATH ="src/logs/keybinds.txt";


const int BLOCKLENGTH = 46;


Screen mainScreen(SCREENWIDTH, SCREENHEIGHT, "Tetris");


const int BSX = SCREENWIDTH/2 - (SCREENWIDTH - (int) (((5.0/16) / 1.5) * SCREENWIDTH))/2;

const int BSY = (int) ((1.0/25) * SCREENHEIGHT);

const int BSW = SCREENWIDTH - (int) ((50.0/96) * SCREENWIDTH);

const int BSH = SCREENHEIGHT - BSY*2;


const int FSY = BSY;

const int FSW = SCREENWIDTH - (FSY*4 + BSW + BSX);

const int FSX = BSX + BSW + (SCREENWIDTH - (BSX + BSW + FSW))/2;

const int FSH = BLOCKLENGTH * 9;


const int ISX = FSX;

const int ISY = FSY + FSH + (SCREENWIDTH - (BSX + BSW) - FSW)/4;

const int ISW = FSW;

const int ISH = BLOCKLENGTH*2;


const int SETTINGSBACKGROUNDX = 50;

const int SETTINGSBACKGROUNDY = SCREENHEIGHT/6;

const int SETTINGSBACKGROUNDW = SCREENWIDTH - SETTINGSBACKGROUNDX*2;

const int SETTINGSBACKGROUNDH = (int) (SCREENHEIGHT/1.5);

const int SETTINGSTEXTUREH = SETTINGSBACKGROUNDH + 200;


const int TEXTURESOUNDX = 0;

int TEXTURESOUNDY;

const int TEXTURESOUNDW = SETTINGSBACKGROUNDW;

int TEXTURESOUNDH;


const int HFX = ISX;

const int HFY = BSY + BSH - BLOCKLENGTH*3;

const int HFW = ISW;

const int HFH = BLOCKLENGTH*2 + (int) (BLOCKLENGTH*(2.0/3));


SDL_Keycode CONTROLLEFT = getFileKeybinds()[0];

SDL_Keycode CONTROLRIGHT = getFileKeybinds()[1];

SDL_Keycode CONTROLDOWN = getFileKeybinds()[2];

SDL_Keycode CONTROLROTATERIGHT = getFileKeybinds()[3];

SDL_Keycode CONTROLROTATELEFT = getFileKeybinds()[4];

SDL_Keycode CONTROLFASTDOWN = getFileKeybinds()[5];

SDL_Keycode CONTROLSWAP = getFileKeybinds()[6];


Uint32 FALLSPEED = 1250;

int SCROLLFACTOR = 20;



unsigned int POINTS = 0;

unsigned int LEVEL = 0;

unsigned int LINES = 0;


int GENERALSOUNDLVL = 50;

int EFFECTSSOUNDLVL = 50;


bool dead = false;


int calculatePoints(int linesCleared){
    switch(linesCleared){
        case 1: 
            return 40*(LEVEL + 1);
        case 2: 
            return 100*(LEVEL + 1);
        case 3:
            return 300*(LEVEL + 1);
        case 4:
            return 1200*(LEVEL + 1);
        default:
            return 0;
    }
}

int getLevel(){
    if (LINES < 10) return 0;
    else if (LINES < 20) return 1;
    else if (LINES < 30) return 2;
    else if (LINES < 40) return 3;
    else if (LINES < 50) return 4;
    else if (LINES < 60) return 5;
    else if (LINES < 70) return 6;
    else if (LINES < 80) return 7;
    else if (LINES < 90) return 8;
    else if (LINES < 100) return 9;
    else if (LINES < 100) return 10;
    else if (LINES < 100) return 11;
    else if (LINES < 120) return 12;
    else if (LINES < 120) return 13;
    else if (LINES < 130) return 14;
    else if (LINES < 130) return 15;
    else if (LINES < 130) return 16;
    else if (LINES < 140) return 17;
    else if (LINES < 140) return 18;
    else if (LINES < 140) return 19;
    else if (LINES < 140) return 20;
    else if (LINES < 150) return 21;
    else if (LINES < 160) return 22;
    else if (LINES < 170) return 23;
    else if (LINES < 180) return 24;
    else if (LINES < 190) return 25;
    else if (LINES < 200) return 26;
    else if (LINES < 200) return 27;
    else if (LINES < 290) return 28;
    else return 29;
}

Uint32 getFallSpeed(){
    if (LEVEL == 0){
        return 799;
    } else if (LEVEL == 1){
        return 715;        
    } else if (LEVEL == 2){
        return 632;        
    } else if (LEVEL == 3){
        return 549;        
    } else if (LEVEL == 4){
        return 466;        
    } else if (LEVEL == 5){
        return 383;        
    } else if (LEVEL == 6){
        return 300;        
    } else if (LEVEL == 7){ //if someone manages to get past this...
        return 216;        
    } else if (LEVEL == 8){
        return 133;        
    } else if (LEVEL == 9){
        return 100;        
    } else if ((LEVEL >= 10) && (LEVEL <= 12)){
        return 83;        
    } else if ((LEVEL >= 13) && (LEVEL <= 15)){
        return 67;        
    } else if ((LEVEL >= 16) && (LEVEL <= 18)){
        return 50;        
    } else if ((LEVEL >= 19) && (LEVEL <= 28)){
        return 33;        
    } else{
        return 17;
    }
}


int py(AbsPosition position, int objH){

    //refers to the Y center of the object you want to position
    int relativeCenterY = objH/2;

    switch(position) {
        case AbsPosition::POS_CENTER:          return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_UP:              return 0;
        case AbsPosition::POS_DOWN:            return SCREENHEIGHT - relativeCenterY*2;
        case AbsPosition::POS_LEFT:            return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_RIGHT:           return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_CENTER_DOWN:     return SCREENHEIGHT/2 - relativeCenterY + SCREENHEIGHT/6;
        case AbsPosition::POS_CENTER_UP:       return SCREENHEIGHT/2 - relativeCenterY - SCREENHEIGHT/6;
        case AbsPosition::POS_CENTER_LEFT:     return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_CENTER_RIGHT:    return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_UP_LEFT:         return 0;
        case AbsPosition::POS_UP_RIGHT:        return 0;
        case AbsPosition::POS_DOWN_LEFT:       return SCREENHEIGHT - relativeCenterY*2;
        case AbsPosition::POS_DOWN_RIGHT:      return SCREENHEIGHT - relativeCenterY*2;
        default:                               return 0;
    }
};

int px(AbsPosition position, int objW){

    //refers to the X center of the object you want to position
    int relativeCenterX = objW/2;

    switch(position) {
        case AbsPosition::POS_CENTER:          return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_UP:              return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_DOWN:            return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_LEFT:            return 0;
        case AbsPosition::POS_RIGHT:           return SCREENWIDTH - relativeCenterX*2;
        case AbsPosition::POS_CENTER_DOWN:     return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_CENTER_UP:       return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_CENTER_LEFT:     return SCREENWIDTH/2 - 2*relativeCenterX;
        case AbsPosition::POS_CENTER_RIGHT:    return SCREENWIDTH/2;
        case AbsPosition::POS_UP_LEFT:         return 0;
        case AbsPosition::POS_UP_RIGHT:        return SCREENWIDTH - relativeCenterX*2;
        case AbsPosition::POS_DOWN_LEFT:       return 0;
        case AbsPosition::POS_DOWN_RIGHT:      return SCREENWIDTH - relativeCenterX*2;
        default:                               return 0;
    }
};

std::string convertKeyToLetter(SDL_Keycode key) {
    switch (key) {

        case SDLK_a: return "A";
        case SDLK_b: return "B";
        case SDLK_c: return "C";
        case SDLK_d: return "D";
        case SDLK_e: return "E";
        case SDLK_f: return "F";
        case SDLK_g: return "G";
        case SDLK_h: return "H";
        case SDLK_i: return "I";
        case SDLK_j: return "J";
        case SDLK_k: return "K";
        case SDLK_l: return "L";
        case SDLK_m: return "M";
        case SDLK_n: return "N";
        case SDLK_o: return "O";
        case SDLK_p: return "P";
        case SDLK_q: return "Q";
        case SDLK_r: return "R";
        case SDLK_s: return "S";
        case SDLK_t: return "T";
        case SDLK_u: return "U";
        case SDLK_v: return "V";
        case SDLK_w: return "W";
        case SDLK_x: return "X";
        case SDLK_y: return "Y";
        case SDLK_z: return "Z";

        case SDLK_0: return "0";
        case SDLK_1: return "1";
        case SDLK_2: return "2";
        case SDLK_3: return "3";
        case SDLK_4: return "4";
        case SDLK_5: return "5";
        case SDLK_6: return "6";
        case SDLK_7: return "7";
        case SDLK_8: return "8";
        case SDLK_9: return "9";

        case SDLK_RETURN: return "ENTER";
        case SDLK_ESCAPE: return "ESCAPE";
        case SDLK_BACKSPACE: return "BACKSPACE";
        case SDLK_TAB: return "TAB";
        case SDLK_SPACE: return "SPACE";
        case SDLK_DELETE: return "DELETE";
        case SDLK_UP: return "UP";
        case SDLK_DOWN: return "DOWN";
        case SDLK_LEFT: return "LEFT";
        case SDLK_RIGHT: return "RIGHT";
        case SDLK_LSHIFT: return "LSHIFT";
        case SDLK_RSHIFT: return "RSHIFT";
        case SDLK_LCTRL: return "LCTRL";
        case SDLK_RCTRL: return "RCTRL";
        case SDLK_LALT: return "LALT";
        case SDLK_RALT: return "RALT";
        case SDLK_CAPSLOCK: return "CAPSLOCK";

        case SDLK_MINUS: return "-";
        case SDLK_EQUALS: return "=";
        case SDLK_LEFTBRACKET: return "[";
        case SDLK_RIGHTBRACKET: return "]";
        case SDLK_BACKSLASH: return "\\";
        case SDLK_SEMICOLON: return ";";
        case SDLK_QUOTE: return "'";
        case SDLK_BACKQUOTE: return "`";
        case SDLK_COMMA: return ",";
        case SDLK_PERIOD: return ".";
        case SDLK_SLASH: return "/";

        case SDLK_KP_0: return "KP_0";
        case SDLK_KP_1: return "KP_1";
        case SDLK_KP_2: return "KP_2";
        case SDLK_KP_3: return "KP_3";
        case SDLK_KP_4: return "KP_4";
        case SDLK_KP_5: return "KP_5";
        case SDLK_KP_6: return "KP_6";
        case SDLK_KP_7: return "KP_7";
        case SDLK_KP_8: return "KP_8";
        case SDLK_KP_9: return "KP_9";
        case SDLK_KP_PLUS: return "KP_PLUS";
        case SDLK_KP_MINUS: return "KP_MINUS";
        case SDLK_KP_MULTIPLY: return "KP_MULTIPLY";
        case SDLK_KP_DIVIDE: return "KP_DIVIDE";
        case SDLK_KP_ENTER: return "KP_ENTER";
        case SDLK_KP_PERIOD: return "KP_PERIOD";

        default:
            return "UNKNOWN";
    }
}

SDL_Keycode convertLetterToKeycode(char c) {
    if (c >= 'a' && c <= 'z') {
        return SDLK_a + (c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
        return SDLK_a + (c - 'A');
    } else if (c >= '0' && c <= '9') {
        return SDLK_0 + (c - '0');
    }

    switch (c) {
        case ' ': return SDLK_SPACE;
        case '\n': return SDLK_RETURN;
        case '\b': return SDLK_BACKSPACE;
        case '\t': return SDLK_TAB;
        case 27:   return SDLK_ESCAPE; // char ESC

        case '-': return SDLK_MINUS;
        case '=': return SDLK_EQUALS;
        case '[': return SDLK_LEFTBRACKET;
        case ']': return SDLK_RIGHTBRACKET;
        case '\\': return SDLK_BACKSLASH;
        case ';': return SDLK_SEMICOLON;
        case '\'': return SDLK_QUOTE;
        case '`': return SDLK_BACKQUOTE;
        case ',': return SDLK_COMMA;
        case '.': return SDLK_PERIOD;
        case '/': return SDLK_SLASH;

        case '*': return SDLK_KP_MULTIPLY;
        case '+': return SDLK_KP_PLUS;

        default:
            return SDLK_UNKNOWN;
    }
}


std::vector <Score> getBestPlays(){
    std::ifstream bestPlaysFile;

    bestPlaysFile.open(BESTPLAYSFILEPATH);

    std::vector <Score> scores;
    
    if(bestPlaysFile.is_open()){
        std::string s;

        while(std::getline(bestPlaysFile, s)){
            Score score;

            std::stringstream game(s);

            char bar;

            game >> score.level >> bar >> score.points >> bar >> score.lines;

            scores.push_back(score);
        }
    }
    
    return scores;
}

bool updateBestPlays(Score newScore){

    std::ofstream bestPlaysFile;
    std::vector <Score> scores = getBestPlays();

    if(scores.size() < 5){
        
        bestPlaysFile.open(BESTPLAYSFILEPATH, std::ios::out | std::ios::app);

        if(bestPlaysFile.is_open()){

            bestPlaysFile << newScore.level << "/" <<  newScore.points << "/" << newScore.lines << "\n";
            
            bestPlaysFile.close();
            
            sortBestPlays();
            return true;
        }

        return false;
    }


    bestPlaysFile.open(BESTPLAYSFILEPATH, std::ios::out);
    
    if(bestPlaysFile.is_open()){

        for(int i = 0; i < (int) scores.size(); i++){
            if((scores[i].level < newScore.level) || 
            ((scores[i].level == newScore.level) && (scores[i].points < newScore.points)) ||
            ((scores[i].level == newScore.level) && (scores[i].points == newScore.points) && (scores[i].lines < newScore.lines))){
                scores[i] = newScore;
                break;
            }
        }

        for(int i = 0; i < (int) scores.size(); i++){
            bestPlaysFile << scores[i].level << "/" <<  scores[i].points << "/" << scores[i].lines << "\n";
        }

        bestPlaysFile.close();
        return true;
    }
        
    return false;
}

bool sortBestPlays(){
    if(getBestPlays().empty() || (getBestPlays().size() == 1)){
        return false;
    }

    std::vector <Score> scores = getBestPlays();
    for(int i = 0; i < (int) scores.size() - 1; i++){
        for(int j = i + 1; j < (int) scores.size(); j++){
            if((scores[i].level < scores[j].level) || 
            ((scores[i].level == scores[j].level) && (scores[i].points < scores[j].points)) ||
            ((scores[i].level == scores[j].level) && (scores[i].points == scores[j].points) && (scores[i].lines < scores[j].lines))){
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    std::ofstream bestPlaysFile;

    bestPlaysFile.open(BESTPLAYSFILEPATH, std::ios::out);
    
    if(bestPlaysFile.is_open()){

        for(int i = 0; i < (int) scores.size(); i++){
            bestPlaysFile << scores[i].level << "/" <<  scores[i].points << "/" << scores[i].lines << "\n";
        }

        bestPlaysFile.close();
        return true;
    }


    return false;
}


std::vector <SDL_Keycode> getFileKeybinds(){
    std::ifstream bestPlaysFile;

    bestPlaysFile.open(KEYBINDSFILEPATH);

    //binds are saved in the following order
    //LEFT, RIGHT, DOWN, ROT RIGHT, ROT LEFT, FAST DOWN, SWAP
    std::vector <SDL_Keycode> keybinds;
    
    if(bestPlaysFile.is_open()){
        std::string s;

        while(std::getline(bestPlaysFile, s)){

            keybinds.push_back((SDL_Keycode) std::stoi(s));
        }
    }
    
    return keybinds;
}

bool updateKeybindsFile(){

    std::ofstream keybindsFile;

    keybindsFile.open(KEYBINDSFILEPATH, std::ios::out);
    
    if(keybindsFile.is_open()){

        for(int i = 0; i < 7; i++){
            switch(i){
                case 0:
                    keybindsFile << CONTROLLEFT;
                    break;
                case 1:
                    keybindsFile << CONTROLRIGHT;
                    break;
                case 2:
                    keybindsFile << CONTROLDOWN;
                    break;
                case 3:
                    keybindsFile << CONTROLROTATERIGHT;
                    break;
                case 4:
                    keybindsFile << CONTROLROTATELEFT;
                    break;
                case 5:
                    keybindsFile << CONTROLFASTDOWN;
                    break;
                case 6:
                    keybindsFile << CONTROLSWAP;
                    break;
                default:
                    break;
            }
            keybindsFile << "\n";
        }

        keybindsFile.close();
        return true;
    }
        
    return false;
}


std::string getRandomMusic(){
    std::string path = "src/Sounds/Music";

    //get a random track (1 to 45)

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rnd45(1,45);

    path += "/" + std::to_string(rnd45(dev)) + ".mp3";

    return path;

}


int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius){
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        //lower right quadrant
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);

        //lower left quadrant
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);

        //upper right quadrant
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);

        //upper left quadrant
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius, bool onlyRightQuadrant){
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        if(onlyRightQuadrant){

            //upper right quadrant
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
    
            //lower right quadrant
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        } else{

            //upper left quadrant
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
    
            //lower left quadrant
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        }   

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius){
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
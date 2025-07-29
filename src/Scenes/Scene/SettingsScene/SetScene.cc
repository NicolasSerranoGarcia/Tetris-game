#include "SetScene.h"

#include <iostream>

SetScene::~SetScene(){
    Scene::~Scene();
}

SetScene::SetScene(){

    open.load("src/Sounds/Effects/openSettings.wav");

    open.play();

    ButtonClick.load("src/Sounds/Effects/clickButton.wav");

    countdown.load("src/Sounds/Effects/countdown.wav");

    ButtonClick.setVolume(EFFECTSSOUNDLVL);
    open.setVolume(EFFECTSSOUNDLVL);
    countdown.setVolume(EFFECTSSOUNDLVL);


    //Setup the keys for an easier loading

        keys = {"rotateRight", "rotateLeft", "left", "right", "down", "fastDown", "swap"};
   
    int highestY = 0;

    for(int i = 0; i < (int) keys.size(); i++){

        Button button(
            //The rectangle
            {(SETTINGSBACKGROUNDW*3)/4 + SETTINGSBACKGROUNDX - (SETTINGSBACKGROUNDW/3 + BLOCKLENGTH)/2, 
            BLOCKLENGTH/2 + SETTINGSBACKGROUNDY + (SETTINGSBACKGROUNDX + 10)*(i+1), 
            SETTINGSBACKGROUNDW/3 + BLOCKLENGTH, 
            SETTINGSBACKGROUNDX}, 
            //Others
            WHITE, &mainScreen);

        getButtonMap()[keys[i]] = button;

        //set the clicked map with the same info as the button map

            mapButtonPressed[keys[i]] = {button, false};

        if(highestY < button.getContainer().y - SETTINGSBACKGROUNDY){
            highestY = button.getContainer().y - SETTINGSBACKGROUNDY;
        }
    }

    //Choose any height of the button, as all of them have the same

        TEXTURESOUNDY = highestY + mapButtonPressed[keys[0]].button.getContainer().h + 15;

        TEXTURESOUNDH = SETTINGSTEXTUREH - TEXTURESOUNDY;

    //Create the right slider 

        Button sliderButton(
            //x
            SETTINGSBACKGROUNDX + SETTINGSBACKGROUNDW - BLOCKLENGTH/3, 
            //y
            SETTINGSBACKGROUNDY,
            //w
             BLOCKLENGTH/3, 
             //h
            (SETTINGSBACKGROUNDH*SETTINGSBACKGROUNDH) / SETTINGSTEXTUREH, 
            GREY, &mainScreen);

        settingsSlider = {sliderButton, SETTINGSBACKGROUNDY, SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH, GREY};

    //Create the sound slider
        
        Button soundSliderButton(getXposFromSoundLvl(SETTINGSBACKGROUNDX + TEXTURESOUNDW/5 - 20), SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15, 40, 40, WHITE, &mainScreen);

        soundSlider = {soundSliderButton, SETTINGSBACKGROUNDX + TEXTURESOUNDW/5 - 20, SETTINGSBACKGROUNDX + 4*TEXTURESOUNDW/5 - 20, WHITE};

        LogicSoundSlider = soundSlider;


    //Create the effects slider

        Button effectsSliderButton(getXposFromEffectsLvl(SETTINGSBACKGROUNDX + TEXTURESOUNDW/5 - 20), SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 12, 40, 40, WHITE, &mainScreen);

        effectsSlider = {effectsSliderButton, SETTINGSBACKGROUNDX + TEXTURESOUNDW/5 - 20, SETTINGSBACKGROUNDX + 4*TEXTURESOUNDW/5 - 20, WHITE};

        LogicEffectsSlider = effectsSlider;

    //Setup the exit button

    //Setup the buttons of the socials and so

        linktree = {SETTINGSBACKGROUNDW/10 + SETTINGSBACKGROUNDX - 25, SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 70, (int) (BLOCKLENGTH*1.2), (int) (BLOCKLENGTH*1.2), LIGHT_GREY, &mainScreen};
        linktreeLogic = linktree;
        linktrr.button= linktreeLogic;
        linktrr.clicked = false;

    //Setup the buttons of the socials and so

        github = {SETTINGSBACKGROUNDW/6 + 10 + SETTINGSBACKGROUNDX - 25, SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 70, (int) (BLOCKLENGTH*1.2), (int) (BLOCKLENGTH*1.2), LIGHT_GREY, &mainScreen};
        githubLogic = github;
        git.button= githubLogic;
        git.clicked = false;

    //Setup the buttons of the socials and so

        instagram = {SETTINGSBACKGROUNDW/6 + 10 + (SETTINGSBACKGROUNDW/6 + 10) - 25 - SETTINGSBACKGROUNDW/10 + SETTINGSBACKGROUNDX, SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 70, (int) (BLOCKLENGTH*1.2), (int) (BLOCKLENGTH*1.2), LIGHT_GREY, &mainScreen};
        instagramLogic = instagram;
        insta.button= instagramLogic;
        insta.clicked = false;

    //Setup the buttons of the radio

        goBackMusic = {23 + SETTINGSBACKGROUNDX + 400 + 180, SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 70, (int) (BLOCKLENGTH*1.2), (int) (BLOCKLENGTH*1.2), LIGHT_GREY, &mainScreen};
        goBackMusicLogic = goBackMusic;
        goBck.button = goBackMusicLogic;
        goBck.clicked = false;

        //go forward

        goForwardMusic = {23 + SETTINGSBACKGROUNDX + 400 + goBackMusic.getContainer().w*2 + 20 + 180, SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 70, (int) (BLOCKLENGTH*1.2), (int) (BLOCKLENGTH*1.2), LIGHT_GREY, &mainScreen};
        goForwardMusicLogic = goForwardMusic;
        goFor.button = goForwardMusicLogic;
        goFor.clicked = false;

        //stop 

        stopMusic = {23 + SETTINGSBACKGROUNDX + 400 + goBackMusic.getContainer().w + 10 + 180, SETTINGSBACKGROUNDY + TEXTURESOUNDY + TEXTURESOUNDH/3 - 20 + 15 + 100 + 70, (int) (BLOCKLENGTH*1.2), (int) (BLOCKLENGTH*1.2), LIGHT_GREY, &mainScreen};
        stopMusicLogic = stopMusic;
        stp.button = stopMusicLogic;
        stp.clicked = false;

        exit = {SETTINGSBACKGROUNDX, SETTINGSBACKGROUNDY, (int) (BLOCKLENGTH*1.3), (int) (BLOCKLENGTH*1.3), LIGHT_GREY, &mainScreen};
        exitLogic = exit;
        ext.button = exitLogic;
        ext.clicked = false;
}


SDL_Rect SetScene::getSourceRect(){
    return sourceRect;
}


void SetScene::setSourceRect(SDL_Rect rect){
    sourceRect = rect;
}


void SetScene::render(){

    //Every time the settings is shown, also show the mainScene in the background

        if(mainScene != nullptr){
            mainScene->renderWithoutFigures();
        }

        Image chains(0, 0, SCREENWIDTH, SCREENHEIGHT, "SetScene-chains", "png");

        chains.CopyToRender();

    //Create a settingsTexture so that we can "slide" trough the settings. It will be set as the render target and all the elements will be render on it

    
        SDL_Texture* settingsTexture = SDL_CreateTexture(mainScreen.getRender(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SETTINGSBACKGROUNDW, SETTINGSTEXTUREH);

        SDL_SetTextureBlendMode(settingsTexture, SDL_BLENDMODE_BLEND);

        SDL_SetRenderTarget(mainScreen.getRender(), settingsTexture);
        
        
        //IMPORTANT: From now on, all the rendering is being made on the settingsTexture


        SDL_SetRenderDrawColor(mainScreen.getRender(), 0, 0, 0, 0);
        SDL_RenderClear(mainScreen.getRender()); 

        Image bg(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-background", "png");

        bg.CopyToRender();

    //Render a title for the keybinds

        Image textBg(0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-textBg", "png");
        Image textBgDecor(0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-textBg-decor", "png");

        textBgDecor.CopyToRender();
        textBg.CopyToRender();

        Image buttonsDec(0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-buttons-dec", "png");

        buttonsDec.CopyToRender();

        Image buttonsT(0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-buttons", "png");

        buttonsT.CopyToRender();


    //Render all the buttons

        for(int i = 0; i < (int) keys.size(); i++){

            //render the button associated with the keybind
            
                Font keybind(&mainScreen, "04B_30__", SETTINGSBACKGROUNDX - 13, convertKeyToLetter(getKeyBindByKey(keys[i])).c_str(), CLEAR_GREY);

                keybind.setCoords(getButtonMap()[keys[i]].getContainer().x + getButtonMap()[keys[i]].getContainer().w/2 - keybind.getTextSurface()->w/2 - SETTINGSBACKGROUNDX, 
                getButtonMap()[keys[i]].getContainer().y + getButtonMap()[keys[i]].getContainer().h/2 - keybind.getTextSurface()->h/2 - SETTINGSBACKGROUNDY);

                keybind.drawTextToRender();

            //Render the text info that comes with the keybind

                //refers to the text that comes with the keybind that says which action is it
                Font infoText(&mainScreen, "04B_30__", SETTINGSBACKGROUNDX - 15, getMessageByKey(keys[i]), CLEAR_BROWN);
                infoText.setCoords(SETTINGSBACKGROUNDW/4 - infoText.getTextSurface()->w/2, getButtonMap()[keys[i].c_str()].getContainer().y - SETTINGSBACKGROUNDY + 5);
            
                infoText.drawTextToRender();

        }

    //If there is a button that has been pressed, render a rectangle above the position of the 
    //button to indicate that it needs to be changed
    
    if(anyButtonPressed){

        //Search for the button that is pressed

        for(auto i = mapButtonPressed.begin(); i != mapButtonPressed.end(); i++){

            if(i->second.clicked){
                renderKeyBindChange(i->second.button, *this);
                break;
            }
        }
    }

    //Render a title for the sound


    
    {
    
    //Render a slider bar for the sound

        int x = TEXTURESOUNDX + TEXTURESOUNDW/5;

        //render the slider

            Image SfxSliderTexture(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-sliders", "png");

            SfxSliderTexture.CopyToRender();

            Slider slider = soundSlider;

            Button button = slider.getSliderButton();

            button.setContainer({button.getContainer().x - SETTINGSBACKGROUNDX, button.getContainer().y - SETTINGSBACKGROUNDY, button.getContainer().w, button.getContainer().h});

            std::string path = "SetScene-slider-button";

            path += isMusicClicked ? "-clicked" : ""; 

            Image ball(button.getContainer().x, button.getContainer().y, button.getContainer().w, button.getContainer().h, path, "png");

            ball.CopyToRender();

    //Render a text for the info of the slider

        Font GeneralSoundText(&mainScreen, "04B_30__", 25, "BGM", BLACK);

        GeneralSoundText.setCoords(TEXTURESOUNDW/2 - GeneralSoundText.getTextSurface()->w/2, TEXTURESOUNDY + TEXTURESOUNDH/3 - 42);

        GeneralSoundText.drawTextToRender();

    }

        Image soundBg(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-sound", "png");

        soundBg.CopyToRender();

    //Render a slider bar for the effects

        int x = TEXTURESOUNDX + TEXTURESOUNDW/5;

        //render the slider

            Slider slider = effectsSlider;

            Button button = slider.getSliderButton();

            button.setContainer({button.getContainer().x - SETTINGSBACKGROUNDX, button.getContainer().y - SETTINGSBACKGROUNDY, button.getContainer().w, button.getContainer().h});
            
            std::string path = "SetScene-slider-button";

            path += isEffectsClicked ? "-clicked" : ""; 

            Image ball(button.getContainer().x, button.getContainer().y, button.getContainer().w, button.getContainer().h, path, "png");

            ball.CopyToRender();

    //Render a text for the info of the slider

        Font GeneralSoundText(&mainScreen, "04B_30__", 25, "SFX", BLACK);

        GeneralSoundText.setCoords(TEXTURESOUNDW/2 - GeneralSoundText.getTextSurface()->w/2, TEXTURESOUNDY + TEXTURESOUNDH/3 - 42 + 100);

        GeneralSoundText.drawTextToRender();
    
        //exit

        {
            Image exitIMG(exit.getContainer().x - SETTINGSBACKGROUNDX, exit.getContainer().y - SETTINGSBACKGROUNDY, exit.getContainer().w, exit.getContainer().h, "SetScene-exit", "png");

            Button exitBtn = exit;

            exitBtn.setContainer({exitBtn.getContainer().x - SETTINGSBACKGROUNDX, exitBtn.getContainer().y - SETTINGSBACKGROUNDY, exitBtn.getContainer().w, exitBtn.getContainer().h});

            std::string path = "SetScene_X";
            path += ext.clicked ? "_Clicked" : "";

            Image image(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, path, "png");

            image.CopyToRender();

        }

        Image iconDecoration(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-icons-decoration", "png");

        iconDecoration.CopyToRender();

    //Render the social buttons
    
        //linktree

        {
            Image linktreeIMG(linktree.getContainer().x - SETTINGSBACKGROUNDX, linktree.getContainer().y - SETTINGSBACKGROUNDY, linktree.getContainer().w, linktree.getContainer().h, linktrr.clicked ? "SetScene-linktree-clicked" : "SetScene-linktree", "png");

            linktreeIMG.CopyToRender();
        }

        //github

        {
            Image githubIMG(github.getContainer().x - SETTINGSBACKGROUNDX, github.getContainer().y - SETTINGSBACKGROUNDY, github.getContainer().w, github.getContainer().h, git.clicked ? "SetScene-github-clicked" : "SetScene-github", "png");

            githubIMG.CopyToRender();
        }

        //instagram

        {
            Image instaIMG(instagram.getContainer().x - SETTINGSBACKGROUNDX, instagram.getContainer().y - SETTINGSBACKGROUNDY, instagram.getContainer().w, instagram.getContainer().h, insta.clicked ? "SetScene-instagram-clicked" : "SetScene-instagram", "png");

            instaIMG.CopyToRender();
        }


    //render the buttons of the song radio

        //rewind

        {
            Image goBackMusicIMG(goBackMusic.getContainer().x - SETTINGSBACKGROUNDX, goBackMusic.getContainer().y - SETTINGSBACKGROUNDY, goBackMusic.getContainer().w, goBackMusic.getContainer().h, goBck.clicked ? "SetScene-rewind-clicked": "SetScene-rewind", "png");

            goBackMusicIMG.CopyToRender();
        }


        //skip song

        {
            Image goForwardMusicIMG(goForwardMusic.getContainer().x - SETTINGSBACKGROUNDX, goForwardMusic.getContainer().y - SETTINGSBACKGROUNDY, goForwardMusic.getContainer().w, goForwardMusic.getContainer().h, goFor.clicked ? "SetScene-skip-clicked": "SetScene-skip", "png");

            goForwardMusicIMG.CopyToRender();

        }


        //stop song

        {
            std::string path = isStoped ? stp.clicked ? "SetScene-resume-clicked" : "SetScene-resume" : stp.clicked ? "SetScene-stop-clicked" : "SetScene-stop";

            Image stopMusicIMG(stopMusic.getContainer().x - SETTINGSBACKGROUNDX, stopMusic.getContainer().y - SETTINGSBACKGROUNDY, stopMusic.getContainer().w, stopMusic.getContainer().h, path, "png");

            stopMusicIMG.CopyToRender();
        }

        Image headers(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-headers", "png");

        headers.CopyToRender();

        Image title(0, 0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200, "SetScene-title", "png");

        title.CopyToRender();



        
    //Set the render target back to the mainScreen
        
        SDL_SetRenderTarget(mainScreen.getRender(), nullptr);
        
    //IMPORTANT: From now on all the rendering is being done on the mainScreen

    //Render the settingsTexture to the screen

        SDL_Rect sourceRect = getSourceRect();

        SDL_Rect destRect = {SETTINGSBACKGROUNDX, SETTINGSBACKGROUNDY, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH};

        SDL_RenderCopy(mainScreen.getRender(), settingsTexture, &sourceRect, &destRect);

    //render the slider to the screen

        settingsSlider.render();

    //render the exit button

    SDL_DestroyTexture(settingsTexture);
}

void SetScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound * music){

    //Set the mainScene that comes from the main as an attribute (for rendering the background)

        if(mainScene == nullptr){
            mainScene = mScene;
        }
    
    //Events that are not one of the listed are not handled

        if((event.type != SDL_KEYDOWN) && (event.type != SDL_KEYUP) && (event.type != SDL_MOUSEBUTTONDOWN) && 
           (event.type != SDL_MOUSEWHEEL) && (event.type != SDL_MOUSEMOTION) && (event.type != SDL_MOUSEBUTTONUP)){
            return;
        }

    //If there is no pressed button and the user presses ESC, return to the game

        if(((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE) && !anyButtonPressed) ||
           (ext.clicked)){

            ext.clicked = false;
                //Show a counter first 

            if(!dead){
                Uint32 current = SDL_GetTicks();
                
                Uint32 next = SDL_GetTicks() + 3000;
                
                if(EFFECTSSOUNDLVL != 0){
                    countdown.play();
                }

                while ((int) ((int) current - (int) next) < 0){
                    SDL_Event e;
                    while(SDL_PollEvent(&e)){
                        if(e.type == SDL_QUIT){
                            SDL_PushEvent(&e);
                            delete curScene;
                            curScene = nullptr;
                            curScene = mScene;
                            mScene = nullptr;
                            curScene->renderWithoutFigures();
                            return;
                        } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                            countdown.stop();
                            return;
                        }
                    }
                    int timer = ceil(abs((int) (next - current))/1000.0);
                    
                    mScene->renderWithoutFigures();
                    
                    Font time(&mainScreen, "04B_30__", 100, std::to_string(timer).c_str(), WHITE);
                    time.setCoords(BSX + BSW/2 - time.getTextSurface()->w/2, BSY + BSH/2 - time.getTextSurface()->h/2);
                    
                    time.drawTextToRender();
                    
                    SDL_RenderPresent(mainScreen.getRender());
                    current = SDL_GetTicks();
                }
            }

            delete curScene;
            curScene = nullptr;
            curScene = mScene;
            mScene = nullptr;
            return;
        }

    //All the "exceptions" are handled at this point


    //If the user clicks on the slider (any of them) or a button, change it's corresponding state

        if((event.type == SDL_MOUSEBUTTONDOWN) && settingsSlider.isClicked(&event)){
            settingsSlider.setClickedNow(true);
        }
        
        if((event.type == SDL_MOUSEBUTTONDOWN) && LogicSoundSlider.isClicked(&event) && LogicSoundSlider.getVisibility()){

            isMusicClicked = true;

            Button button = LogicSoundSlider.getSliderButton();

            int y = LogicSoundSlider.getSliderButton().getContainer().y;
            int w = LogicSoundSlider.getSliderButton().getContainer().w;
            int h = LogicSoundSlider.getSliderButton().getContainer().h;

            if(((y + h) > (SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH)) && button.isClickedSubdivision(&event, {0, 0, w, h - ((y + h) - (SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH))})){
                LogicSoundSlider.setClickedNow(true);
                soundSlider.setClickedNow(true);
            }

            else if ((y + h) < (SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH)){
                LogicSoundSlider.setClickedNow(true);
                soundSlider.setClickedNow(true);   
            }
        } 

        if((event.type == SDL_MOUSEBUTTONUP) && isMusicClicked){
            isMusicClicked = false;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && LogicEffectsSlider.isClicked(&event) && LogicEffectsSlider.getVisibility()){

            isEffectsClicked = true;

            Button button = LogicEffectsSlider.getSliderButton();

            int y = LogicEffectsSlider.getSliderButton().getContainer().y;
            int w = LogicEffectsSlider.getSliderButton().getContainer().w;
            int h = LogicEffectsSlider.getSliderButton().getContainer().h;

            if(((y + h) > (SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH)) && button.isClickedSubdivision(&event, {0, 0, w, h - ((y + h) - (SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH))})){
                LogicEffectsSlider.setClickedNow(true);
                effectsSlider.setClickedNow(true);
            }

            else if ((y + h) < (SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH)){
                LogicEffectsSlider.setClickedNow(true);
                effectsSlider.setClickedNow(true);
            }
        }

        if((event.type == SDL_MOUSEBUTTONUP) && isEffectsClicked){
            isEffectsClicked = false;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && linktreeLogic.isClicked(&event)){
            linktrr.clicked = true;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && githubLogic.isClicked(&event)){
            git.clicked = true;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && instagramLogic.isClicked(&event)){
            insta.clicked = true;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && goBackMusicLogic.isClicked(&event)){
            goBck.clicked = true;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && goForwardMusicLogic.isClicked(&event)){
            goFor.clicked = true;
        }

        if((event.type == SDL_MOUSEBUTTONDOWN) && stopMusicLogic.isClicked(&event)){
            stp.clicked = true;
        }

         if((event.type == SDL_MOUSEBUTTONDOWN) && exitLogic.isClicked(&event)){
            ext.clicked = true;
        }

    //If the user, on the other hand, lets go the click, change the slider state consequently

        if((event.type == SDL_MOUSEBUTTONUP) && settingsSlider.getClickedNow()){
            settingsSlider.setClickedNow(false);
        }

        if((event.type == SDL_MOUSEBUTTONUP) && LogicSoundSlider.getClickedNow()){
            LogicSoundSlider.setClickedNow(false);
            soundSlider.setClickedNow(false);
        }

        if((event.type == SDL_MOUSEBUTTONUP) && LogicEffectsSlider.getClickedNow()){
            LogicEffectsSlider.setClickedNow(false);
            effectsSlider.setClickedNow(false);
        }

        if((event.type == SDL_MOUSEBUTTONUP) && linktrr.clicked){
            system("xdg-open https://linktr.ee/NicolasSerrano");
            linktrr.clicked = false;
        }

        if((event.type == SDL_MOUSEBUTTONUP) && git.clicked){
            system("xdg-open https://github.com/NicolasSerranoGarcia");
            git.clicked = false;
        }

        if((event.type == SDL_MOUSEBUTTONUP) && insta.clicked){
            insta.clicked = false;
            system("xdg-open https://www.instagram.com/nicolasserranogarcia/");
        }

        if((event.type == SDL_MOUSEBUTTONUP) && goBck.clicked){
            goBck.clicked = false;
            music->load(getSong("previous"));
            music->play();
            isStoped = false;
        }

        if((event.type == SDL_MOUSEBUTTONUP) && goFor.clicked){
            goFor.clicked = false;
            music->load(getSong("next"));
            music->play();
            isStoped = false;
        }

        if((event.type == SDL_MOUSEBUTTONUP) && stp.clicked){
            stp.clicked = false;
            isStoped ? music->resume() : music->pause();
            isStoped = !isStoped;
        }

        if((event.type == SDL_MOUSEBUTTONUP) && ext.clicked){
            ext.clicked = false;
        }

    //If the user is currently clicking the slider and moves the mouse, update the settings

        if((event.type == SDL_MOUSEMOTION) && settingsSlider.getClickedNow()) {

            //Faster access

                Button sliderBtn = settingsSlider.getSliderButton();
                int sliderX = sliderBtn.getContainer().x;
                int sliderY = sliderBtn.getContainer().y;
                int sliderW = sliderBtn.getContainer().w;
                int sliderH = sliderBtn.getContainer().h;

                int sliderMin = settingsSlider.getMin();
                int sliderMax = settingsSlider.getMax();

                int newY = sliderY + event.motion.yrel;

            //This sets newY to be inside the limits of the settings
            
                newY = std::max(sliderMin, std::min(newY, sliderMax - sliderH));

            // set the slider to the new position

                sliderBtn.setContainer({sliderX, newY, sliderW, sliderH});
                settingsSlider.setSliderButton(sliderBtn);

            //Calculate the proportional movement of the slider

                int sliderTrackH = sliderMax - sliderMin - sliderH;

                int scrollRange = SETTINGSTEXTUREH - SETTINGSBACKGROUNDH;

            // Make sure we dont divide by 0 when calculating the relation

                int sliderOffset = newY - sliderMin;

                float sliderRatio = (sliderTrackH > 0) ? ((float)sliderOffset / sliderTrackH) : 0.0f;

            SDL_Rect newSrc = getSourceRect();
            newSrc.y = (int)(sliderRatio * scrollRange);
            setSourceRect(newSrc);

           //update the buttons accordingly

                auto maps = getButtonMap();
                for(auto i = maps.begin(); i != maps.end(); i++) {

                    i->second.setContainer({i->second.getContainer().x, i->second.getContainer().y - newSrc.y, i->second.getContainer().w, i->second.getContainer().h});

                    mapButtonPressed[i->first].button = i->second;
                }

            //update the sound slider

                Button s = soundSlider.getSliderButton();

                s.setContainer({s.getContainer().x, soundSlider.getSliderButton().getContainer().y - newSrc.y, s.getContainer().w, s.getContainer().h});

                LogicSoundSlider.setSliderButton(s);

                if(LogicSoundSlider.getSliderButton().getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    LogicSoundSlider.setVisibility(false);
                } else {
                    LogicSoundSlider.setVisibility(true);
                }

            //update the effects slider

                s = effectsSlider.getSliderButton();

                s.setContainer({s.getContainer().x, effectsSlider.getSliderButton().getContainer().y - newSrc.y, s.getContainer().w, s.getContainer().h});

                LogicEffectsSlider.setSliderButton(s);

                if(LogicEffectsSlider.getSliderButton().getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    LogicEffectsSlider.setVisibility(false);
                } else {
                    LogicEffectsSlider.setVisibility(true);
                }


            //update the linktree button

                linktreeLogic.setContainer({linktree.getContainer().x, linktree.getContainer().y - newSrc.y, linktree.getContainer().w, linktree.getContainer().h});

                if(linktreeLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    linktreeLogic.setVisibility(false);
                } else {
                    linktreeLogic.setVisibility(true);
                }

            //update the github button

                githubLogic.setContainer({github.getContainer().x, github.getContainer().y - newSrc.y, github.getContainer().w, github.getContainer().h});

                if(githubLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    githubLogic.setVisibility(false);
                } else {
                    githubLogic.setVisibility(true);
                }


            //update the instagram button

                instagramLogic.setContainer({instagram.getContainer().x, instagram.getContainer().y - newSrc.y, instagram.getContainer().w, instagram.getContainer().h});

                if(instagramLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    instagramLogic.setVisibility(false);
                } else {
                    instagramLogic.setVisibility(true);
                }


            // update the rewind button

                goBackMusicLogic.setContainer({goBackMusic.getContainer().x, goBackMusic.getContainer().y - newSrc.y, goBackMusic.getContainer().w, goBackMusic.getContainer().h});

                if(goBackMusicLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    goBackMusicLogic.setVisibility(false);
                } else {
                    goBackMusicLogic.setVisibility(true);
                }


            //update the skip button

                goForwardMusicLogic.setContainer({goForwardMusic.getContainer().x, goForwardMusic.getContainer().y - newSrc.y, goForwardMusic.getContainer().w, goForwardMusic.getContainer().h});

                if(goForwardMusicLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    goForwardMusicLogic.setVisibility(false);
                } else {
                    goForwardMusicLogic.setVisibility(true);
                }


            // update the stop button

                stopMusicLogic.setContainer({stopMusic.getContainer().x, stopMusic.getContainer().y - newSrc.y, stopMusic.getContainer().w, stopMusic.getContainer().h});

                if(stopMusicLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    stopMusicLogic.setVisibility(false);
                } else {
                    stopMusicLogic.setVisibility(true);
                }


                exitLogic.setContainer({exit.getContainer().x, exit.getContainer().y - newSrc.y, exit.getContainer().w, exit.getContainer().h});

                if(exitLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    exitLogic.setVisibility(false);
                } else {
                    exitLogic.setVisibility(true);
                }
        }

        if((event.type == SDL_MOUSEMOTION) && LogicSoundSlider.getClickedNow() && LogicSoundSlider.getVisibility()){

            //Faster access

                Button sliderBtn = soundSlider.getSliderButton();
                int sliderX = sliderBtn.getContainer().x;
                int sliderY = sliderBtn.getContainer().y;
                int sliderW = sliderBtn.getContainer().w;
                int sliderH = sliderBtn.getContainer().h;

                int sliderMin = soundSlider.getMin();
                int sliderMax = soundSlider.getMax();

                int newX = sliderX + event.motion.xrel;

            //This sets newX to be inside the limits of the settings
            
                newX = std::max(sliderMin, std::min(newX, sliderMax));

            // set the slider to the new position

                sliderBtn.setContainer({newX, sliderY, sliderW, sliderH});
                soundSlider.setSliderButton(sliderBtn);

                sliderBtn = LogicSoundSlider.getSliderButton();
                sliderX = sliderBtn.getContainer().x;
                sliderY = sliderBtn.getContainer().y;
                sliderW = sliderBtn.getContainer().w;
                sliderH = sliderBtn.getContainer().h;

                sliderBtn.setContainer({newX, sliderY, sliderW, sliderH});
                LogicSoundSlider.setSliderButton(sliderBtn);

            //Calculate the % of the sound

                int newSoundLevel =(int) (100 * ((double) (newX - soundSlider.getMin())/ (soundSlider.getMax() - soundSlider.getMin())));

                GENERALSOUNDLVL = newSoundLevel;

            }

        if((event.type == SDL_MOUSEMOTION) && LogicEffectsSlider.getClickedNow() && effectsSlider.getVisibility()){

            //Faster access

                Button sliderBtn = effectsSlider.getSliderButton();
                int sliderX = sliderBtn.getContainer().x;
                int sliderY = sliderBtn.getContainer().y;
                int sliderW = sliderBtn.getContainer().w;
                int sliderH = sliderBtn.getContainer().h;

                int sliderMin = effectsSlider.getMin();
                int sliderMax = effectsSlider.getMax();

                int newX = sliderX + event.motion.xrel;

            //This sets newX to be inside the limits of the settings
            
                newX = std::max(sliderMin, std::min(newX, sliderMax));

            // set the slider to the new position

                sliderBtn.setContainer({newX, sliderY, sliderW, sliderH});
                effectsSlider.setSliderButton(sliderBtn);

                sliderBtn = LogicEffectsSlider.getSliderButton();
                sliderX = sliderBtn.getContainer().x;
                sliderY = sliderBtn.getContainer().y;
                sliderW = sliderBtn.getContainer().w;
                sliderH = sliderBtn.getContainer().h;

                sliderBtn.setContainer({newX, sliderY, sliderW, sliderH});
                LogicEffectsSlider.setSliderButton(sliderBtn);

            //Calculate the % of the sound

                int newSoundLevel = (int) (100 * ((double) (newX - effectsSlider.getMin())/ (effectsSlider.getMax() - effectsSlider.getMin())));

                EFFECTSSOUNDLVL = newSoundLevel;

                ButtonClick.setVolume(EFFECTSSOUNDLVL);
                open.setVolume(EFFECTSSOUNDLVL);
                countdown.setVolume(EFFECTSSOUNDLVL);
            }

    //If the user is currently scrolling, update the settings

        if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0) {

            SDL_Rect newSrc = getSourceRect();

            int scrollRange = SETTINGSTEXTUREH - SETTINGSBACKGROUNDH;

            int sliderMin = settingsSlider.getMin();
            int sliderMax = settingsSlider.getMax();

            Button sliderBtn = settingsSlider.getSliderButton();

            SDL_Rect sliderRect = sliderBtn.getContainer();

            int sliderTrackH = sliderMax - sliderMin - sliderRect.h;


            int scrollDir = (event.wheel.y > 0) ? -1 : 1;

            int delta = SCROLLFACTOR * scrollDir;

            //Recalculate the new limits of the source rect

                int newY = newSrc.y + delta;
                newY = std::max(0, std::min(newY, scrollRange));
                newSrc.y = newY;
                setSourceRect(newSrc);

            // Having the new source rect, recalculate the slider position
                
                float ratio = (float)newSrc.y / scrollRange;
                int sliderY = sliderMin + (int)(ratio * sliderTrackH);
                sliderBtn.setContainer({sliderRect.x, sliderY, sliderRect.w, sliderRect.h});
                settingsSlider.setSliderButton(sliderBtn);

            //update the buttons

                auto maps = getButtonMap();
                for(auto i = maps.begin(); i != maps.end(); i++) {
                    SDL_Rect orig = i->second.getContainer();
                    i->second.setContainer({orig.x, orig.y - newSrc.y, orig.w, orig.h});
                    mapButtonPressed[i->first].button = i->second;
                }

            //update the sound slider

                Button s = soundSlider.getSliderButton();

                s.setContainer({s.getContainer().x, soundSlider.getSliderButton().getContainer().y - newSrc.y, s.getContainer().w, s.getContainer().h});

                LogicSoundSlider.setSliderButton(s);

                if(LogicSoundSlider.getSliderButton().getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    LogicSoundSlider.setVisibility(false);
                } else {
                    LogicSoundSlider.setVisibility(true);
                }


            // update the effects slider

                s = effectsSlider.getSliderButton();

                s.setContainer({s.getContainer().x, effectsSlider.getSliderButton().getContainer().y - newSrc.y, s.getContainer().w, s.getContainer().h});

                LogicEffectsSlider.setSliderButton(s);

                if(LogicEffectsSlider.getSliderButton().getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    LogicEffectsSlider.setVisibility(false);
                } else {
                    LogicEffectsSlider.setVisibility(true);
                }


            //update the linktree button

                linktreeLogic.setContainer({linktreeLogic.getContainer().x, linktree.getContainer().y - newSrc.y, linktree.getContainer().w, linktree.getContainer().h}); 

                if(linktreeLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    linktreeLogic.setVisibility(false);
                } else {
                    linktreeLogic.setVisibility(true);
                }


            //update the github button

                githubLogic.setContainer({githubLogic.getContainer().x, github.getContainer().y - newSrc.y, github.getContainer().w, github.getContainer().h}); 

                if(githubLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    githubLogic.setVisibility(false);
                } else {
                    githubLogic.setVisibility(true);
                }


            //update the instagram button

                instagramLogic.setContainer({instagramLogic.getContainer().x, instagram.getContainer().y - newSrc.y, instagram.getContainer().w, instagram.getContainer().h}); 

                if(instagramLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    instagramLogic.setVisibility(false);
                } else {
                    instagramLogic.setVisibility(true);
                }

            
            //update the rewind button

                goBackMusicLogic.setContainer({goBackMusicLogic.getContainer().x, goBackMusic.getContainer().y - newSrc.y, goBackMusic.getContainer().w, goBackMusic.getContainer().h});

                if(goBackMusicLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    goBackMusicLogic.setVisibility(false);
                } else {
                    goBackMusicLogic.setVisibility(true);
                }


            //update the skip button

                goForwardMusicLogic.setContainer({goForwardMusicLogic.getContainer().x, goForwardMusic.getContainer().y - newSrc.y, goForwardMusic.getContainer().w, goForwardMusic.getContainer().h});

                if(goForwardMusicLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    goForwardMusicLogic.setVisibility(false);
                } else {
                    goForwardMusicLogic.setVisibility(true);
                }

            //update the stop button

                stopMusicLogic.setContainer({stopMusicLogic.getContainer().x, stopMusic.getContainer().y - newSrc.y, stopMusic.getContainer().w, stopMusic.getContainer().h});

                if(stopMusicLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    stopMusicLogic.setVisibility(false);
                } else {
                    stopMusicLogic.setVisibility(true);
                }


                exitLogic.setContainer({exitLogic.getContainer().x, exit.getContainer().y - newSrc.y, exit.getContainer().w, exit.getContainer().h});

                if(exitLogic.getContainer().y > SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
                    exitLogic.setVisibility(false);
                } else {
                    exitLogic.setVisibility(true);
                }

            return;
        }

    for(auto i = mapButtonPressed.begin(); i != mapButtonPressed.end(); i++){

        //easier access

            Button curButton = i->second.button;

            int y = i->second.button.getContainer().y;
            int w = i->second.button.getContainer().w;
            int h = i->second.button.getContainer().h;

        //Also use the loop if there is a button that needs to change it's visibility

            //when the whole button is outside of the screen, set the visibility to false.
            //otherwise true

            curButton.setVisibility((y + h) > sourceRect.y);


            if(i->second.clicked){
                if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym != SDLK_ESCAPE)){

                    //returns a reference
                    getKeyBindByKey(i->first) = event.key.keysym.sym;
                    updateKeybindsFile();

                    anyButtonPressed = false;
                    i->second.clicked = false;
                    return;
                }

                else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)){
                    i->second.clicked = false;
                    anyButtonPressed = false;
                    return;
                }
            }



        if(curButton.getVisibility() && curButton.isClicked(&event)){

            if(((y < SETTINGSBACKGROUNDY) && curButton.isClickedSubdivision(&event, {0, SETTINGSBACKGROUNDY - y, w, h - (SETTINGSBACKGROUNDY - y)})) || 
                 y > SETTINGSBACKGROUNDY){

                for(auto i = mapButtonPressed.begin(); i != mapButtonPressed.end(); i++){
                    if(i->second.clicked){
                        i->second.clicked = false;
                    }
                }

                ButtonClick.play();
                i->second.clicked = true;
                anyButtonPressed = true;
            }
        }
    }
}

void SetScene::renderAllButtons(std::map <std::string, Button> map){
    for (auto i = map.begin(); i != map.end(); i++){
        
        i->second.setContainer({i->second.getContainer().x - SETTINGSBACKGROUNDX, i->second.getContainer().y - SETTINGSBACKGROUNDY, i->second.getContainer().w, i->second.getContainer().h});
        i->second.drawToRender();

        SDL_Rect rect = i->second.getContainer();
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &rect);

        i->second.setContainer({i->second.getContainer().x + SETTINGSBACKGROUNDX, i->second.getContainer().y + SETTINGSBACKGROUNDY, i->second.getContainer().w, i->second.getContainer().h});

    }
}

void SetScene::renderButton(Button button){

    button.setContainer({button.getContainer().x - SETTINGSBACKGROUNDX, button.getContainer().y - SETTINGSBACKGROUNDY, button.getContainer().w, button.getContainer().h});

    button.drawToRender();

    SDL_Rect rect = button.getContainer();
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &rect);
}


//FUNCTIONS

void renderKeyBindChange(Button button, SetScene & s){

    SDL_Rect coverRect = {button.getContainer().x - SETTINGSBACKGROUNDX,
                          button.getContainer().y - SETTINGSBACKGROUNDY + s.getSourceRect().y,
                          button.getContainer().w,
                          button.getContainer().h};

    Image cover(0, button.getContainer().y - (BLOCKLENGTH/2 + SETTINGSBACKGROUNDY + (SETTINGSBACKGROUNDX + 10)) + s.getSourceRect().y - 9, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH + 200 + 90, "SetScene-button-cover", "png");

    cover.CopyToRender();

    Font coverFont(&mainScreen, "Ubuntu-BoldItalic", 30, "...", BLACK);
    coverFont.setCoords(coverRect.x + coverRect.w/2 - coverFont.getTextSurface()->w/2, coverRect.y + coverRect.h/2 - coverFont.getTextSurface()->h/2);
    coverFont.drawTextToRender();    
}

SDL_Keycode& getKeyBindByKey(std::string key){

    if(key == "rotateRight"){
        return CONTROLROTATERIGHT;
    } 
    else if(key == "rotateLeft"){
        return CONTROLROTATELEFT;
    } 
    else if(key == "left"){
        return CONTROLLEFT;
    } 
    else if(key == "right"){
        return CONTROLRIGHT;
    } 
    else if(key == "down"){
        return CONTROLDOWN;
    } 
    else if(key == "fastDown"){
        return CONTROLFASTDOWN;
    } 
    else if(key == "swap"){
        return CONTROLSWAP;
    }

    return CONTROLFASTDOWN;
}

const char * getMessageByKey(std::string key){

    if(key == "rotateRight"){
        return "rotate right";
    } 
    else if(key == "rotateLeft"){
        return "rotate left";
    } 
    else if(key == "left"){
        return "move left";
    } 
    else if(key == "right"){
        return "move right";
    } 
    else if(key == "down"){
        return "move down";
    } 
    else if(key == "fastDown"){
        return "fast Down";
    } 
    else if(key == "swap"){
        return "swap figure";
    }

    return "Unknown";
}

int getXposFromSoundLvl(int minX){
    return  (int) minX + ((GENERALSOUNDLVL/100.0)*(SETTINGSBACKGROUNDX + 4*TEXTURESOUNDW/5 - 20.0 - minX));
}

int getXposFromEffectsLvl(int minX){
    return  (int) minX + ((EFFECTSSOUNDLVL/100.0)*(SETTINGSBACKGROUNDX + 4*TEXTURESOUNDW/5 - 20.0 - minX));
}
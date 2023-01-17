#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

void
GameWindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./grass.png");

    for(int i = 0; i < Num_WasteType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", WasteClass[i]);
        waste[i] = al_load_bitmap(buffer);
    }

    player = al_load_bitmap("./3.png");
    npc_graph = al_load_bitmap("./npc.png");
    win_graph = al_load_bitmap("./win.jpg");
    lose_graph = al_load_bitmap("./lose.jpg");

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    // voice

    sample = al_load_sample("hayaku.wav");
    hintSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hintSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hintSound, al_get_default_mixer());

    sample = al_load_sample("lose.wav");
    loseSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(loseSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(loseSound, al_get_default_mixer());

    sample = al_load_sample("win.wav");
    winSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(winSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(winSound, al_get_default_mixer());

    sample = al_load_sample("hayakugirl.mp3");
    hintSoundgirl = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hintSoundgirl, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hintSoundgirl, al_get_default_mixer());

    sample = al_load_sample("begin.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());


    sample = al_load_sample("digvoice.wav");
    digSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(digSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(digSound, al_get_default_mixer());

    sample = al_load_sample("correctvoice.wav");
    correctSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(correctSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(correctSound, al_get_default_mixer());

    sample = al_load_sample("wrongvoice.wav");
    wrongSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(wrongSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(wrongSound, al_get_default_mixer());

    sample = al_load_sample("papervoice.wav");
    paperSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(paperSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(paperSound, al_get_default_mixer());

    //player set initial value.
    gamer.set_posx(200);
    gamer.set_posy(200);
    gamer.set_height(al_get_bitmap_height(player));
    gamer.set_width(78);
    gamer.set_chance(10);
    gamer.set_hint(50);
    gamer.set_goal(30);
    dig = gamer.get_chance();
    hint = gamer.get_hint();

    // NPC
    npc.set_posx(500);
    npc.set_posy(500);
    npc.set_height(al_get_bitmap_height(player));
    npc.set_width(78);
    npc.set_time(10);

    //load waste.
    init_grid();

    print_grid();

    level = new LEVEL(1);
    menu = new Menu();
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    npc_timer = al_create_timer(2.5 / FPS);
    npc_move_timer = al_create_timer(3);


    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(npc_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(npc_move_timer));

    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));


    al_start_timer(timer);
    al_start_timer(npc_timer);
    al_start_timer(npc_move_timer);

}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{

    mute = false;
    redraw = false;
    menu->Reset();

    al_stop_sample_instance(startSound);


    // stop timer
    al_stop_timer(timer);
    al_stop_timer(npc_timer);
    al_stop_timer(npc_move_timer);

}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(npc_timer);
    al_destroy_timer(npc_move_timer);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(waste[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(hintSound);
    al_destroy_sample_instance(digSound);
    al_destroy_sample_instance(hintSoundgirl);
    al_destroy_sample_instance(correctSound);
    al_destroy_sample_instance(wrongSound);
    al_destroy_sample_instance(winSound);
    al_destroy_sample_instance(loseSound);
    delete level;
    delete menu;
}

int
GameWindow::process_event()
{
    int instruction = GAME_CONTINUE;

    // offset for pause window
    int offsetX = field_width/2 - 200;
    int offsetY = field_height/2 - 200;

    al_wait_for_event(event_queue, &event);
    redraw = false;
    //npc.update();

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if (event.timer.source == npc_timer){
            npc.update();
        }
        if (event.timer.source == npc_move_timer){
            npc.set_speed(3);
        }
        if(event.timer.source == timer) {
            /*if (!flagforhint){
                std::cout << "move\n" ;
                npc.update();
            }*/

            redraw = true;

            if(Coin_Inc_Count == 0)
                //menu->Change_Coin(Coin_Time_Gain);

            Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;

        }
        else {
            if(Monster_Pro_Count == 0) {
                //Monster *m = create_monster();

                //if(m != NULL)
                    //monsterSet.push_back(m);
            }
            //Monster_Pro_Count = (Monster_Pro_Count + 1) % level->getMonsterSpeed();
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_SPACE:
                al_play_sample_instance(digSound);
                al_rest(0.1);
                if (gamer.dig()){
                    al_play_sample_instance(correctSound);
                    al_rest(0.1);
                    score = gamer.get_point();
                    if (grid[gamer.get_gridx()][gamer.get_gridy()].get_type() == 3){
                        al_rest(0.6);
                        al_play_sample_instance(paperSound);
                    }
                }
                else{
                    al_play_sample_instance(wrongSound);
                }
                dig = gamer.get_chance();
                break;
            case ALLEGRO_KEY_H:
                if (hint){
                    npc.set_speed(0);
                    hint_res = gamer.use_hint();
                    hint = gamer.get_hint();
                    al_play_sample_instance(hintSound);
                    al_rest(1.5);
                    al_play_sample_instance(hintSoundgirl);
                    flagforhint = false;
                }

                break;
            case ALLEGRO_KEY_ESCAPE:
                return GAME_EXIT;
        }
    }
    switch(event.keyboard.keycode) {
        // character control
        case ALLEGRO_KEY_W:
            gamer.moveUp();
            sourceX += (al_get_bitmap_width(player) / 8);
            sourceX %= al_get_bitmap_width(player);
            break;
        case ALLEGRO_KEY_A:
            gamer.moveLeft();
            sourceX += (al_get_bitmap_width(player) / 8);
            sourceX %= al_get_bitmap_width(player);
            break;
        case ALLEGRO_KEY_S:
            gamer.moveDown();
            sourceX += (al_get_bitmap_width(player) / 8);
            sourceX %= al_get_bitmap_width(player);
            break;
        case ALLEGRO_KEY_D:
            gamer.moveRight();
            sourceX += (al_get_bitmap_width(player) / 8);
            sourceX %= al_get_bitmap_width(player);
            break;
    }

    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;

    al_clear_to_color(al_map_rgb(100, 100, 100));
    if (gamer.isWin()){
        al_play_sample_instance(winSound);
        al_draw_bitmap(win_graph, 0, 0, 0);
    }
    else if (gamer.isLose() || map_empty()){
        al_play_sample_instance(loseSound);
        al_draw_bitmap(lose_graph, 0, 0, 0);
    }
    else
    {   al_draw_bitmap(background, 0, 0, 0);

        // draw the player.
        for (int i=1 ; i<=12 ; i++){
            al_draw_line(0, i*50, 800, i*50, al_map_rgb(255, 255, 255), 3);
        }
        for (int i=1 ; i<=16 ; i++){
            al_draw_line(i*50, 0, i*50, 600, al_map_rgb(255, 255, 255), 3);
        }
        al_draw_bitmap_region(player, sourceX, gamer.get_state() * al_get_bitmap_height(player) / 4, 78, 77, gamer.get_posx(), gamer.get_posy(), NULL);
        al_draw_bitmap_region(npc_graph, npc_sourceX, npc.get_state() * al_get_bitmap_height(player) / 4, 78, 77, npc.get_posx(), npc.get_posy(), NULL);

        draw_waste();



        al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(80, 80, 80));

        menu->Draw();
    }

    al_flip_display();
}

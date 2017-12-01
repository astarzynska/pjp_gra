#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <time.h>

const float FPS = 60;

//hgujhg

int main() {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY *pytania = NULL;
	ALLEGRO_BITMAP *player = NULL;
	ALLEGRO_BITMAP *straznik = NULL;
	ALLEGRO_BITMAP *gwiazda = NULL;
	ALLEGRO_BITMAP *gwiazda1 = NULL;
	ALLEGRO_BITMAP *gwiazda2 = NULL;
	ALLEGRO_BITMAP *kometa = NULL;
	ALLEGRO_EVENT_QUEUE *kolejka = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	int x_gw, y_gw = 30;
	int x_gw1, y_gw1 = 0;
	int x_gw2, y_gw2 = 0;
	int x_kom, y_kom, dx_kom, dy_kom;
	float x_player = 0, y_player = 520;
	int x_straz = 800, y_straz = 520;
	int left = 0;
	bool ok = true;
	int proba = 0, proba2 = 0, proba3=0;
	int stars = 0, punkty = 0;
	int bez_nast = 0, bez_nast2=0;
	int super_moc = 1, koniec8=1;
	float dx_gw = 1, dx_gw1 = 3, dx_gw2 = 2;
	int okno = 0;


	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font("mini.ttf", 15, NULL);

	ALLEGRO_KEYBOARD_STATE *keyboard;
	al_install_keyboard();

	srand(time(NULL));

	display = al_create_display(900, 600);
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());

	player = al_load_bitmap("panda2.png");
	straznik = al_load_bitmap("straznik3.png");
	gwiazda = al_load_bitmap("gwiazda.png");
	gwiazda1 = al_load_bitmap("gwiazda1.png");
	gwiazda2 = al_load_bitmap("gwiazda2.png");
	kometa = al_load_bitmap("kometa.png");

	al_clear_to_color(al_map_rgb(0, 0, 96));
	al_draw_text(font, al_map_rgb(255, 255, 255), 700, 10, 0, "PUNKTY:");
	al_draw_text(font, al_map_rgb(255, 255, 255), 500, 10, 0, "LOST STARS:");

	al_draw_bitmap(player, x_player, y_player, NULL);//(x,y) okreslaja lewy gorny rog a os Y jest skierowana w dol
	al_draw_bitmap(straznik, x_straz, y_straz, NULL);

	x_gw = rand() % 880 + 1;
	x_gw1 = rand() % 880 + 1;
	x_gw2 = rand() % 880 + 1;
	x_kom = rand() % 870 + 1;
	y_kom = rand() % 270 + 30;

	al_draw_bitmap(gwiazda, x_gw, y_gw, NULL);
	//al_draw_bitmap(gwiazda1, x_gw1, y_gw1, NULL);
	//al_draw_bitmap(gwiazda2, x_gw2, y_gw2, NULL);
	al_draw_bitmap(kometa, x_kom, y_kom, NULL);

	al_draw_filled_rectangle(0, 570, 900, 600, al_map_rgb(255, 64, 0));
	al_draw_filled_rectangle(0, 0, 900, 30, al_map_rgb(0, 0, 0));

	al_flip_display();

	//al_rest(3.0);

	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(kolejka, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (ok) {

		ALLEGRO_EVENT event;
		al_wait_for_event(kolejka, &event);


		if (event.type == ALLEGRO_EVENT_TIMER && left == 0) {
			/*switch (left)
			{
			case 1:
			x_player = x_player - 5;
			y_gw = y_gw + 20;
			break;
			case 2:
			x_player = x_player + 5;
			y_gw = y_gw + 20;
			break;
			}*/


			y_gw = y_gw + dx_gw;
			if (x_kom < 450 && proba == 0) {
				x_kom = x_kom + 2;
				proba = 1;
			}
			else {
				x_kom = x_kom - 2;
			}
			y_kom = y_kom + 2;

			if (punkty % 3 == 0 && punkty!=0 && bez_nast==0 ) {
				y_gw1 = y_gw1 + dx_gw1;
				
			}
			if (punkty % 4 == 0 && punkty != 0 && bez_nast2 == 0) {
				y_gw2 = y_gw2 + dx_gw2;

			}
			/*if (x_player < x_straz) {
			x_straz = x_straz - 3;
			}
			else if (x_player > x_straz){
			x_straz = x_straz + 3;
			}*/
			left = 1;


		}

		if (event.type = ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{

			case ALLEGRO_KEY_LEFT:
				//left = 1;
				if (super_moc == 0) {
					x_player = x_player - 10;
				}
				else {
					x_player = x_player - 5;
				}
				break;

			case ALLEGRO_KEY_RIGHT:
				//left = 2;
				if (super_moc == 0) {
					x_player = x_player + 10;
				}
				else {
					x_player = x_player + 5;
				}
				break;

			case ALLEGRO_KEY_UP:
				y_player = y_player - 15;
				break;

			case ALLEGRO_KEY_DOWN:
				y_player = y_player + 15;
				break;

			case ALLEGRO_KEY_ESCAPE:
				ok = false;
				break;

			}
		}
		if (x_player <= -5) {
			x_player = 0;
		}
		if (y_player >= 565) {
			y_player = 520;
		}
		if (x_player >= 855) {
			x_player = 850;
		}
		if (y_player <= 430) {
			y_player = 475;
		}

		if (y_gw > 570 && proba2 == 0) {
			stars = stars - 1;
			x_gw = rand() % 880 + 1;
			y_gw = 30;
			proba2 = 1;
		}

		if ((x_gw > x_player) && (x_gw < x_player + 50) && (y_gw == y_player)) {
			punkty = punkty + 1;
			x_gw = rand() % 880 + 1;
			y_gw = 30;
		}
		if ((x_gw1 > x_player) && (x_gw1 < x_player + 50) && (y_gw1 >518 && y_gw1<523)) {
			super_moc = 0;
			x_gw1 = rand() % 880 + 1;
			y_gw1 = 0;
			bez_nast = 1;
		}
		if ((x_gw2 > x_player) && (x_gw2 < x_player + 50) && (y_gw2 >518 && y_gw2<523)) {
			x_gw2 = rand() % 880 + 1;
			y_gw2 = 0;
			bez_nast2 = 1;
		}

		if (y_gw1 > 570) {
			x_gw1 = rand() % 880 + 1;
			y_gw1 = 0;
			bez_nast = 1;
		}
		if (y_gw2 > 570) {
			x_gw2 = rand() % 880 + 1;
			y_gw2 = 0;
			bez_nast2 = 1;
		}
		if (punkty % 3 != 0) {
			bez_nast = 0;
			super_moc = 1;
		}
		if (punkty % 4 != 0) {
			bez_nast2 = 0;
		}
		if (punkty % 8 == 0 && koniec8==0) {
			dx_gw = 2 * dx_gw;
			dx_gw1 = 2 * dx_gw1;
			dx_gw2 = 2 * dx_gw2;
			koniec8 = 1;
		}
		if (punkty % 8 != 0) {
			koniec8 = 0;
		}
		if (stars == (-10) && okno==0) {
			pytania = al_create_display(400, 200);
			al_clear_to_color(al_map_rgb(50, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 450, 250, 0, "Pytania:");
			al_flip_display();
			al_rest(3.0);
			al_destroy_display(pytania);
			okno = 1;
			//ok = false;
		}

		al_draw_bitmap(player, x_player, y_player, NULL);
		al_draw_bitmap(straznik, x_straz, y_straz, NULL);
		//al_draw_text(font, al_map_rgb(255, 255, 255), 450, 250, 0, "Pytania:");
		al_draw_filled_rectangle(0, 0, 900, 30, al_map_rgb(0, 0, 0));
		al_draw_textf(font, al_map_rgb(255, 255, 255), 700, 10, 0, "PUNKTY: %i", punkty);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 10, 0, "LOST STARS: %i", stars);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 96));
		al_draw_bitmap(gwiazda, x_gw, y_gw, NULL);
		al_draw_bitmap(gwiazda1, x_gw1, y_gw1, NULL);
		al_draw_bitmap(gwiazda2, x_gw2, y_gw2, NULL);
		al_draw_bitmap(kometa, x_kom, y_kom, NULL);

		al_draw_filled_rectangle(0, 570, 900, 600, al_map_rgb(255, 64, 0));
		left = 0;
		proba2 = 0;
	}

	al_destroy_bitmap(player);
	al_destroy_display(display);
	al_destroy_bitmap(gwiazda);
	al_destroy_bitmap(gwiazda1);
	al_destroy_bitmap(gwiazda2);
	al_destroy_event_queue(kolejka);
	al_destroy_timer(timer);
	

	return 0;


}

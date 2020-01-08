/**
 * @file DrumExperiment.c
 * @author  david ponarovsky
 * @version 1.0
 * @date 9 Sep 2014
 *
 * @brief System to keep track of the cooking times.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The system keeps track of the cooking times.
 * Input  : Times to be measured.
 * Process: Summing times if needed, waiting for the correct time and
 *          notifying the user.
 * Output : Notification.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
// ... rest of includes from the system
// ... all my includes

// -------------------------- const definitions -------------------------

const int WAVESIZE = 100;
const int MAXSTARS = 20;


// ------------------------------ functions -----------------------------
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */


void error_call() {
	  fputs("ERROR\n" , stderr);
		exit(0);
}

 /**
  * @brief The main function. Actually, does nothing here.
  * @return 0, to tell the system the execution ended without errors.
  */
float aggregate_before_dot(float ret, int pressed, int position) {
	return (float)(10 * ret) + (pressed - '0');
}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
float aggregate_after_dot(float ret, int pressed, int position) {
	return ret + ( (float)(pressed - '0') / position);
}

typedef float (*read_func)(float ret, int pressed, int position);

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
char peek_stdin() {
		char ret = getchar();
		ungetc(ret, stdin);
		return ret;
}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
float read_float()
{
		int pressed, position = 10, step=0;
		float ret = 0;
		read_func aggregate[2] = { &aggregate_before_dot, &aggregate_after_dot };
		while( (peek_stdin()) != '\n' && (pressed = getchar()) != SPACE) {
				if (pressed != '.' ) {

					if ( pressed < '0' || pressed > '9' ){
							error_call();
					}

					ret = aggregate[step](ret, pressed, position);
					position = (step ? position * 10 : position);
				}
				else {
					step++;
				}
		}
		return ret;
}

void centerallize(float * wave, int length) {
		float centerallized_wave[WAVESIZE];
		int hist = (WAVESIZE - length)/2, i =0;

		for (i = 0; i < hist; i++) {
			centerallized_wave[i] = 0;
		}
		for (; i < hist + length; i++) {
			centerallized_wave[i] = wave[i - hist];
		}
		for (; i < WAVESIZE; i++) {
			centerallized_wave[i] = 0;
		}
		i = 0;
		for (; i < WAVESIZE; i++) {
			wave[i] = centerallized_wave[i];
		}
}

void normallized(float * wave) {
		float sum = 0;
		for(int i=0; i < WAVESIZE; i++){
			sum += wave[i];
		}
		if (sum) {
			for(int i=0; i < WAVESIZE; i++){
				wave[i] /= sum;
			}
		}
}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int read_wave(float * wave){
		int i;
		for (i = 0; i < WAVESIZE && (peek_stdin()) != '\n'; i++) {
				wave[i] = read_float();
		}
		getchar();
		return i;
}


int generate_wave(float * wave){
		int length = read_wave(wave);
		centerallize(wave, length);
		normallized(wave);
		return length;
}

void init_array(float * arr, int length) {
		for (int i = 0; i < length; i++) {
				arr[i] = 0;
		}
}

void conv(float * wave_f, float * wave_g, float * wave_result, int f_length, int g_length){
		init_array(wave_result, WAVESIZE);

		int f_hist = (WAVESIZE - f_length)/2;
		int g_hist = (WAVESIZE - g_length)/2;

		// for (int i = f_hist; i < f_hist + f_length; i++) {
		// 		for (int j = -(g_length)/2; j <= g_length/2; j++) {
		// 				wave_result[i] += wave_f[i - j]*wave_g[g_hist + j];
		// 		}
		// }

		// for (int i = -WAVESIZE / 2; i < WAVESIZE/2 ; i++) {
		// 		for (int j = -WAVESIZE / 2; j < WAVESIZE/2 ; j++) {
		// 				wave_result[WAVESIZE/2 + i] += wave_f[ WAVESIZE/2 + i - j]*wave_g[ WAVESIZE/2 + j];
		// 		}
		// }
		// for (int i = WAVESIZE / 2; i < WAVESIZE ; i++) {
		// 		for (int j = -WAVESIZE / 2; j < WAVESIZE/2 ; j++) {
		// 				wave_result[i] += wave_f[i - j]*wave_g[ WAVESIZE/2 + j];
		// 		}
		// }
		// for (int i = 0; i < WAVESIZE/2 ; i++) {
		// 		for (int j = -WAVESIZE / 2; j < WAVESIZE/2 ; j++) {
		// 				wave_result[i] += wave_f[ WAVESIZE/2 + i - j]*wave_g[ WAVESIZE/2 + j];
		// 		}
		// }
		for (int j = 0; j < WAVESIZE; j++) {
				for (int i = 0; i <= WAVESIZE/2; i++) {
						if ( i >= j)
							wave_result[WAVESIZE/2 + i] += wave_f[j]*wave_g[i-j];
						//printf("%f * %f \n",wave_f[j], wave_g[i-j] );
				}
				for (int i = WAVESIZE/2 + 1; i < WAVESIZE; i++) {
						if ( i >= j)
							wave_result[i - WAVESIZE/2] += wave_f[j]*wave_g[i-j];
						//printf("%f * %f \n",wave_f[j], wave_g[i-j] );
				}
		}
		normallized(wave_result);
}


void conv_power_n(float * wave_f, float * wave_g, float * wave_result, int n) {
		float * swap_pointer = wave_f;
		for (int i = 0; i < n; i++) {
				init_array(wave_result, WAVESIZE);
				//conv( wave_f, wave_g, wave_result);
				wave_f = wave_result;
				wave_result = swap_pointer;
				swap_pointer = wave_f;
		}
}

float max_arr(float * arr, int n) {
		float _max = arr[0];
		for (int i = 0; i < n; i++) {
				if ( _max < arr[i] ) {
					_max = arr[i];
				}
		}
		return _max;
}

void round3 (float * wave) {
		for (int i = 0; i < WAVESIZE; i++) {
				wave[i] =  (float) (round(1000*wave[i]) / 1000 );
		}
}

float set_number_of_stars(float * wave, int * stars) {
		round3(wave);
		float _max = max_arr(wave, WAVESIZE);
		for (int i = 0; i < WAVESIZE; i++) {
				stars[i] = 20 * ( (float) wave[i] / _max );
		}
}

void print_histogram(float * wave, int * stars) {
		for ( int i = 0; i < WAVESIZE; i++) {
				printf("%0.3f:", wave[i] );
				for( int j = 1; j <= stars[i]; j++) {
						putchar('*');
				}
				putchar('\n');
		}
}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int main()
{
	char buff[WAVESIZE];
	float h_wave[WAVESIZE], g_wave[WAVESIZE], wave_result[WAVESIZE];
	int stars[WAVESIZE];
	int i = 0 , n;
	int g_length = generate_wave(g_wave);
	int h_length = generate_wave(h_wave);
	scanf("%d", &n);
	//
	// for (i = 0; i < 3; i++) {
	// 	gcvt(h_wave[i], 8, buff);
	// 	printf("%s\n", buff );
	// }
	// for (i = 0; i < 3; i++) {
	// 	gcvt(g_wave[i], 8, buff);
	// 	printf("%s\n", buff );
	// }
	//conv_power_n(h_wave, g_wave, wave_result, n);
	float *ret;
	for(i = 0; i < n; i++){
		if ( i % 2 == 0)
			conv(g_wave, h_wave, wave_result, g_length, h_length);
		else
			conv(wave_result, h_wave, g_wave, g_length, h_length);
	}
	ret = n%2 == 0 ? g_wave : wave_result;
	//conv(g_wave, h_wave, wave_result, g_length, h_length);
	// conv(h_wave, wave_result, g_wave, h_length, g_length);
	// conv(h_wave, g_wave, wave_result, h_length, g_length);
	// conv(h_wave, wave_result, g_wave, h_length, g_length);
	set_number_of_stars(ret, stars);
	print_histogram(ret, stars);
	// float ret = read_float() + 5;
	// gcvt(ret, 8, buff);
	// printf("%s\n", buff );

	return 0;
}

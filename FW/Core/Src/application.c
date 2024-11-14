/*
 * application.c
 *
 *  Created on: Nov 14, 2024
 *      Author: Misi
 */

#include "application.h"

uint16_t spectrum[SPECTRUM_SIZE];


double gaussian(int x, int mean, double std_dev) {
    return exp(-0.5 * pow((x - mean) / std_dev, 2.0));
}
void generate_spectrum(uint16_t *spectrum, uint16_t peak_height) {
// Generate background noise
	 for (int i = 0; i < SPECTRUM_SIZE; i++) {
		 spectrum[i] = BACKGROUND_LEVEL + rand() % 3; // Random background noise
	 }

	 // Add Compton continuum
	 for (int i = 0; i < COMPTON_EDGE; i++) {
		 spectrum[i] += (COMPTON_EDGE - i) / 20 + rand() % 2;
	 }

	 // Add Gaussian photopeak around the PEAK_POSITION
	 for (int i = PEAK_POSITION - 4 * PEAK_WIDTH; i < PEAK_POSITION + 4 * PEAK_WIDTH; i++) {
		 if (i >= 0 && i < SPECTRUM_SIZE) {
			 double gaussian_value = peak_height * exp(-0.5 * pow((i - PEAK_POSITION) / (double)PEAK_WIDTH, 2.0));
			 spectrum[i] += (uint16_t)(gaussian_value) + rand() % 3;
		 }
	 }
}

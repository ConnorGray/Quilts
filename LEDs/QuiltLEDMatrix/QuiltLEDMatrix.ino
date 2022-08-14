#include <FastLED.h>

#define NUM_LEDS 100
#define DATA_PIN 6

CRGB LED_DATA[NUM_LEDS];

const u8 WIDTH = 10;
const u8 HEIGHT = 10;

//========
// Points
//========

typedef u8 uint8_t;

struct Point {
	u8 x;
	u8 y;
};

size_t PointToIndex(Point p) {
	int mirrorFactor = p.x % 2 == 0 ? p.y : (HEIGHT - p.y- 1);

	return (p.x * HEIGHT + mirrorFactor);
}


void setPoint(Point p, CRGB color) {
	if (!IsInBounds(p)) {
		return;
	}

	LED_DATA[PointToIndex(p)] = color;
}

bool IsInBounds(Point p) {
	return p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT;
}

void setAll(CRGB color) {
	for (int i = 0; i < NUM_LEDS; i++) {
		LED_DATA[i] = color;
	}
}


//==============
// Letter logic
//==============

static const Point Letter_A[] = {{ .x = 0, .y = 0 }, { .x = 4, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 3, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_B[] = {{ .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 3, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_C[] = {{ .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 0, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_D[] = {{ .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_E[] = {{ .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 0, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 0, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_F[] = {{ .x = 0, .y = 0 }, { .x = 0, .y = 1 }, { .x = 0, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 0, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_G[] = {{ .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 3, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_H[] = {{ .x = 0, .y = 0 }, { .x = 4, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 3, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 4, .y = 5 }};
static const Point Letter_I[] = {{ .x = 0, .y = 0 }, { .x = 0, .y = 1 }, { .x = 0, .y = 2 }, { .x = 0, .y = 3 }, { .x = 0, .y = 4 }, { .x = 0, .y = 5 }};
static const Point Letter_J[] = {{ .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 4, .y = 2 }, { .x = 4, .y = 3 }, { .x = 4, .y = 4 }, { .x = 4, .y = 5 }};
static const Point Letter_K[] = {{ .x = 0, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 3, .y = 1 }, { .x = 0, .y = 2 }, { .x = 2, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 0, .y = 4 }, { .x = 2, .y = 4 }, { .x = 0, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_L[] = {{ .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 0, .y = 2 }, { .x = 0, .y = 3 }, { .x = 0, .y = 4 }, { .x = 0, .y = 5 }};
static const Point Letter_M[] = {{ .x = 0, .y = 0 }, { .x = 4, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 2, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 1, .y = 4 }, { .x = 3, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 4, .y = 5 }};
static const Point Letter_N[] = {{ .x = 0, .y = 0 }, { .x = 4, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 3, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 2, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 1, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 4, .y = 5 }};
static const Point Letter_O[] = {{ .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_P[] = {{ .x = 0, .y = 0 }, { .x = 0, .y = 1 }, { .x = 0, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 3, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_Q[] = {{ .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 4, .y = 0 }, { .x = 0, .y = 1 }, { .x = 3, .y = 1 }, { .x = 0, .y = 2 }, { .x = 2, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_R[] = {{ .x = 0, .y = 0 }, { .x = 4, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 3, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};
static const Point Letter_S[] = {{ .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 4, .y = 1 }, { .x = 4, .y = 2 }, { .x = 1, .y = 3 }, { .x = 2, .y = 3 }, { .x = 3, .y = 3 }, { .x = 0, .y = 4 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }, { .x = 4, .y = 5 }};
static const Point Letter_T[] = {{ .x = 2, .y = 0 }, { .x = 2, .y = 1 }, { .x = 2, .y = 2 }, { .x = 2, .y = 3 }, { .x = 0, .y = 4 }, { .x = 1, .y = 4 }, { .x = 2, .y = 4 }, { .x = 3, .y = 4 }, { .x = 4, .y = 4 }};
static const Point Letter_U[] = {{ .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }};
static const Point Letter_V[] = {{ .x = 2, .y = 0 }, { .x = 1, .y = 1 }, { .x = 3, .y = 1 }, { .x = 1, .y = 2 }, { .x = 3, .y = 2 }, { .x = 0, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }};
static const Point Letter_W[] = {{ .x = 1, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 2, .y = 1 }, { .x = 4, .y = 1 }, { .x = 0, .y = 2 }, { .x = 2, .y = 2 }, { .x = 4, .y = 2 }, { .x = 0, .y = 3 }, { .x = 4, .y = 3 }, { .x = 0, .y = 4 }, { .x = 4, .y = 4 }};
static const Point Letter_X[] = {{ .x = 0, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 3, .y = 1 }, { .x = 1, .y = 2 }, { .x = 2, .y = 2 }, { .x = 0, .y = 3 }, { .x = 3, .y = 3 }, { .x = 0, .y = 4 }, { .x = 3, .y = 4 }};
static const Point Letter_Z[] = {{ .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2, .y = 0 }, { .x = 3, .y = 0 }, { .x = 0, .y = 1 }, { .x = 1, .y = 2 }, { .x = 2, .y = 3 }, { .x = 3, .y = 4 }, { .x = 0, .y = 5 }, { .x = 1, .y = 5 }, { .x = 2, .y = 5 }, { .x = 3, .y = 5 }};


void drawLetterWithOffset(char letter, CRGB color, size_t xOffset, size_t yOffset) {
	Point* data = 0;
	size_t len = 0;

	switch (letter) {
		case 'A':
			data = Letter_A;
			len = sizeof(Letter_A) / sizeof(Letter_A[0]);
			break;
		case 'B':
			data = Letter_B;
			len = sizeof(Letter_B) / sizeof(Letter_B[0]);
			break;
		case 'C':
			data = Letter_C;
			len = sizeof(Letter_C) / sizeof(Letter_C[0]);
			break;
		case 'D':
			data = Letter_D;
			len = sizeof(Letter_D) / sizeof(Letter_D[0]);
			break;
		case 'E':
			data = Letter_E;
			len = sizeof(Letter_E) / sizeof(Letter_E[0]);
			break;
		case 'F':
			data = Letter_F;
			len = sizeof(Letter_F) / sizeof(Letter_F[0]);
			break;
		case 'G':
			data = Letter_G;
			len = sizeof(Letter_G) / sizeof(Letter_G[0]);
			break;
		case 'H':
			data = Letter_H;
			len = sizeof(Letter_H) / sizeof(Letter_H[0]);
			break;
		case 'I':
			data = Letter_I;
			len = sizeof(Letter_I) / sizeof(Letter_I[0]);
			break;
		case 'J':
			data = Letter_J;
			len = sizeof(Letter_J) / sizeof(Letter_J[0]);
			break;
		case 'K':
			data = Letter_K;
			len = sizeof(Letter_K) / sizeof(Letter_K[0]);
			break;
		case 'L':
			data = Letter_L;
			len = sizeof(Letter_L) / sizeof(Letter_L[0]);
			break;
		case 'M':
			data = Letter_M;
			len = sizeof(Letter_M) / sizeof(Letter_M[0]);
			break;
		case 'N':
			data = Letter_N;
			len = sizeof(Letter_N) / sizeof(Letter_N[0]);
			break;
		case 'O':
			data = Letter_O;
			len = sizeof(Letter_O) / sizeof(Letter_O[0]);
			break;
		case 'P':
			data = Letter_P;
			len = sizeof(Letter_P) / sizeof(Letter_P[0]);
			break;
		case 'Q':
			data = Letter_Q;
			len = sizeof(Letter_Q) / sizeof(Letter_Q[0]);
			break;
		case 'R':
			data = Letter_R;
			len = sizeof(Letter_R) / sizeof(Letter_R[0]);
			break;
		case 'S':
			data = Letter_S;
			len = sizeof(Letter_S) / sizeof(Letter_S[0]);
			break;
		case 'T':
			data = Letter_T;
			len = sizeof(Letter_T) / sizeof(Letter_T[0]);
			break;
		case 'U':
			data = Letter_U;
			len = sizeof(Letter_U) / sizeof(Letter_U[0]);
			break;
		case 'V':
			data = Letter_V;
			len = sizeof(Letter_V) / sizeof(Letter_V[0]);
			break;
		case 'W':
			data = Letter_W;
			len = sizeof(Letter_W) / sizeof(Letter_W[0]);
			break;
		case 'X':
			data = Letter_X;
			len = sizeof(Letter_X) / sizeof(Letter_X[0]);
			break;
		case 'Z':
			data = Letter_Z;
			len = sizeof(Letter_Z) / sizeof(Letter_Z[0]);
			break;

		case ' ':
			data = {};
			len = 0;
			break;

		default:
			data = Letter_A;
			len = sizeof(Letter_A) / sizeof(Letter_A[0]);
	}

	for (int i = 0; i < len; i++) {
		Point p = data[i];

		p.x += xOffset;
		p.y += yOffset;

		setPoint(p, color);
	}
}

void drawLetter(char letter) {
	drawLetterWithOffset(letter, CRGB::Green, 0, 0);
}

//======================
// Text animation logic
//======================

const int LETTER_HEIGHT = 7;
void verticalAnimateText(char* letters, size_t len) {
	size_t yOffset = 0;

	size_t textHeight = LETTER_HEIGHT * len;

	for (int h = 0; h < textHeight; h++) {
		setAll(CRGB::Black);

		for (int c = 0; c < len; c++) {
			char letter = letters[c];
			CRGB color = c % 2 == 0 ? CRGB::Green : CRGB::Blue;
			drawLetterWithOffset(letter, color, 0, -c * LETTER_HEIGHT + yOffset);
		}

		FastLED.show();

		delay(150);

		yOffset += 1;
	}
}

//================
// Color patterns
//================

void fillRandomPoints(size_t count) {
	int n = 0;

	setAll(CRGB::Black);

	for (int i = 0; i < count; i++) {
		int x = random(WIDTH);
		int y = random(HEIGHT);

		Point p = { .x = x, .y = y};

		CRGB color = CRGB::Black;
		switch (i % 3) {
			case 0: color = CRGB::Red;   break;
			case 1: color = CRGB::Green; break;
			case 2: color = CRGB::Blue;  break;
			default: color = CRGB::Purple;
		}

		setPoint(p, color);

		FastLED.show();
		delay(50);
	}
}

//-----
// Rain
//-----

void rain() {
	const CRGB black = CRGB::Black;

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			const Point point = { .x = x, .y = y};
			const CRGB color = LED_DATA[PointToIndex(point)];

			if (color != black) {
				const CRGB tail = {
					.r = max(color.r - 50, 0),
					.g = max(color.g - 50, 0),
					.b = max(color.b - 50, 0)
				};

				setPoint(point, tail);

				setPoint({ .x = point.x, .y = point.y - 1}, color);
			}
		}
	}

	if (random(300) > 1) {
		setPoint({.x = random(WIDTH), .y = HEIGHT - 1}, CRGB::White);
	}

	FastLED.show();
	delay(100);
}

//----------------
// Fighting lights
//----------------

static u8 remaining_blue = 0;
static u8 remaining_red = 0;

const CRGB RED = CRGB::Red;
const CRGB BLUE = CRGB::Blue;

void fightingLights() {
	//-----------
	// Start Blue
	//-----------

	if (random(30) > 25) {
		remaining_blue = random(2) + 2;
	}

	if (remaining_blue > 0) {
		LED_DATA[0] = CRGB::Blue;
		remaining_blue -= 1;
	} else {
		LED_DATA[0] = CRGB::Black;
	}

	//-----------
	// Start Red
	//-----------

	if (random(30) > 25) {
		remaining_red = random(2) + 2;
	}

	if (remaining_red > 0) {
		LED_DATA[NUM_LEDS - 1] = CRGB::Red;
		remaining_red -= 1;
	} else {
		LED_DATA[NUM_LEDS - 1] = CRGB::Black;
	}

	//-----------
	// Advance
	//-----------

	for (int i = NUM_LEDS - 1; i >= 1; i -= 1) {
		if (LED_DATA[i - 1] == BLUE) {
			LED_DATA[i] = BLUE;
			LED_DATA[i - 1] = CRGB::Black;
		}
	}

	for (int i = 1; i < NUM_LEDS - 1; i += 1) {
		if (LED_DATA[i + 1] == RED) {
			LED_DATA[i] = RED;
			LED_DATA[i + 1] = CRGB::Black;
		}
	}

	// for (int i = 1; i < NUM_LEDS - 1; i += 1) {
	// 	if (LED_DATA[i + 1] == RED) {
	// 		LED_DATA[i] = RED;
	// 		LED_DATA[i + 1] = CRGB::Black;
	// 	}
	// 	// if (!saw_red) {
	// 	// 	LED_DATA[i] = LED_DATA[i - 1];
	// 	// } else {
	// 	// 	LED_DATA[i] = LED_DATA[i + 1];
	// 	// }
	// }

	FastLED.show();
	delay(100);
}

//===========
// Main Loop
//===========

void setup() {
	Serial.begin(9600);

	// put your setup code here, to run once:
	FastLED.addLeds<WS2812B, 3, RGB>(LED_DATA, NUM_LEDS);
	//  FastLED.addLeds<NEOPIXEL, 3>(LED_DATA, NUM_LEDS);

	FastLED.showColor(CRGB::Black);
	FastLED.show();

	setAll(CRGB::Black);
}

void loop() {
	//===========
	// Draw text
	//===========

	// char* letters = "HELLO PEORIA";

	// verticalAnimateText(letters, strlen(letters));

	// delay(150);

	//===========
	// Draw fill one point at a time
	//===========

	// fillRandomPoints(200);

	//===========
	// Rain
	//===========

	// rain();

	//===========
	// Fighting lights
	//===========

	fightingLights();
}

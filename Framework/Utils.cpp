#include <ctime>
#include "Utils.h"
#include "Defines.h"

int Utils::p = Utils::GenerateRandomPrime();
int Utils::q = Utils::GenerateRandomPrime();
int Utils::n = p * q;
int Utils::z = (p - 1) * (q - 1);
int Utils::e = Utils::GetPublicKeyExponent(z);
int Utils::d = Utils::GetPrivateKeyExponent(e, z);


void Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect width, height

	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);
}

void Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	SetOrigin(obj, originPreset, obj.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	SetOrigin(obj, originPreset, obj.getLocalBounds());

}

void Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	SetOrigin(obj, originPreset, obj.getLocalBounds());
}

// 두 Random 값은 같음
sf::Vector2f Utils::GetRandomVector2(float start, float end)
{
	float randVal = (rand() % ((int)(end * 100) - (int)(start * 100))) + start * 100;
	return sf::Vector2f(randVal / 100, randVal / 100);
}


float Utils::GetRandomAngle()
{
	return (float)(rand() / RAND_MAX) * 360.f;
}

int Utils::GetGCD(int a, int b)
{
	int temp;
	if (a < b) {
		temp = a;
		a = b;
		b = temp;
	}
	if (b == 0)
		return a;
	else {
		return GetGCD(b, a % b);
	}
}

int Utils::GetPrivateKeyExponent(int exponent, int z)
{
	exponent = exponent % z;
	for (int i = 1; i < z; i++)
		if ((exponent * i) % z == 1)
			return i;
	return 1;
}

int Utils::Encrypt(int message, int exponent, int n)
{
	int result = 1;
	message = message % n;
	while (exponent > 0) {
		if (exponent % 2 == 1)
			result = (result * message) % n;
		exponent = exponent / 2;
		message = (message * message) % n;
	}
	return result;
}

int Utils::Decrypt(int cipherText, int exponent, int n)
{
	int result = 1;
	cipherText = cipherText % n;
	while (exponent > 0) {
		if (exponent % 2 == 1)
			result = (result * cipherText) % n;
		exponent = exponent / 2;
		cipherText = (cipherText * cipherText) % n;
	}
	return result;
}

bool Utils::IsPrime(int number)
{
	if (number == 1) return false;
	if (number == 2 || number == 3) return true;
	for (int i = 2; i * i <= number; i++) {
		if (number % i == 0) return false;
	}
	return true;
}

int Utils::GenerateRandomPrime(int min, int max)
{
	srand(time(NULL));

	int primeNumber = (rand() % min + 1) + max;
	while (!IsPrime(primeNumber))
		primeNumber = (rand() % min + 1) + max;

	return primeNumber;
}

int Utils::GetPublicKeyExponent(int exponent)
{
	int e = SHRT_MAX;

	while (GetGCD(e, exponent) != 1) e++;

	return e;
}

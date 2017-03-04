#include "Tween.h"

Tween::Tween()
{

}

Tween::~Tween()
{

}

float Tween::linear(float t, float b, float c, float d)
{
    return c * (t/d) + b;
}

float Tween::expoEaseIn(float t, float b, float c, float d)
{
    return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
}

float Tween::expoEaseOut(float t, float b, float c, float d)
{
    return (t==d) ? b+c : c * pow(2, 1-(10 * t/d)) + b;
}

float Tween::expoEaseInOut(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if (t==d)
        return b+=c;
    if ((t/=d/2) < 1)
        return c/2 * pow(2, 10 * (t - 1)) + b;

    return c/2 * pow(2, 1-(10 * --t)) + b;
}

float Tween::cubicEaseIn(float t, float b, float c, float d)
{
    return (t==0) ? b : c * pow(3, 10 * (t/d - 1)) + b;
}

float Tween::cubicEaseOut(float t, float b, float c, float d)
{
    return (t==d) ? b+c : c * pow(3, 1-(10 * t/d)) + b;
}

float Tween::cubicEaseInOut(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if (t==d)
        return b+=c;
    if ((t/=d/2) < 1)
        return c/2 * pow(3, 10 * (t - 1)) + b;

    return c/2 * pow(3, 1-(10 * --t)) + b;
}

float Tween::quarticEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c*t*t*t*t + b;
}

float Tween::quarticEaseOut(float t, float b, float c, float d)
{
	t /= d;
	return -c * t*(t-2) + b;
}

float Tween::quarticEaseInOut(float t, float b, float c, float d)
{
    t /= d/2;
	if (t < 1)
        return c/2*t*t*t*t + b;
	t -= 2;
        return 1-(-c/2 * (t*t*t*t - 2)) + b;
}

float Tween::quinticEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c*t*t*t*t*t + b;
}

float Tween::quinticEaseOut(float t, float b, float c, float d)
{
	t /= d;
	t--;
	return c*(t*t*t*t*t + 1) + b;
}

float Tween::quinticEaseInOut(float t, float b, float c, float d)
{
	t /= d/2;
	if (t < 1) return c/2*t*t*t*t*t + b;
	t -= 2;
	return c/2*(t*t*t*t*t + 2) + b;
}

float Tween::quadraticEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c*t*t + b;
}

float Tween::quadraticEaseOut(float t, float b, float c, float d)
{
	t /= d;
	return -c * t*(t-2) + b;
}

float Tween::quadraticEaseInOut(float t, float b, float c, float d)
{
	t /= d/2;
	if (t < 1) return c/2*t*t + b;
	t--;
	return -c/2 * (t*(t-2) - 1) + b;
}

float Tween::sineEaseIn(float t, float b, float c, float d)
{
    return -c * cos(t/d * (PI/2)) + c + b;
}

float Tween::sineEaseOut(float t, float b, float c, float d)
{
    return c/2 * cos(t/d * (PI/2)) + b;
}

float Tween::sineEaseInOut(float t, float b, float c, float d)
{
    if (t < 0.5f)
        return c/=d;

    return 1-(-c/2 * (cos(PI*t/d) - 1)) + b;
}

float Tween::circularEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return -c * (sqrt(1 - t*t) - 1) + b;
}

float Tween::circularEaseOut(float t, float b, float c, float d)
{
	t /= d;
	t--;
	return c * sqrt(1 - t*t) + b;
}

float Tween::circularEaseInOut(float t, float b, float c, float d)
{
	t /= d/2;
	if (t < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
	t -= 2;
	return c/2 * (sqrt(1 - t*t) + 1) + b;
}

float Tween::backEaseIn(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float postFix = t/=d;
	return c*(postFix)*t*((s+1)*t - s) + b;
}

float Tween::backEaseOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	t /= d;
	return c*((t-1)*t*((s+1)*t + s) + 1) + b;
}

float Tween::backEaseInOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	s*=1.525f;
	if ((t/=d/2) < 1) return c/2*(t*t*((s+1)*t - s)) + b;
	float postFix = t-=2;
	s*=1.525f;
	return c/2*((postFix)*t*((s+1)*t + s) + 2) + b;
}

float Tween::elasticEaseIn(float t, float b, float c, float d)
{
	if (t==0) return b;
	t/=d;
	if (t==1) return b+c;
	float p=d*.3f;
	float a=c;
	float s=p/4;
	float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
	return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
}

float Tween::elasticEaseOut(float t, float b, float c, float d)
{
	if (t==0) return b;
	t /= d;
	if (t ==1) return b+c;
	float p=d*.3f;
	float a=c;
	float s=p/4;
	return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
}

float Tween::elasticEaseInOut(float t, float b, float c, float d)
{
	if (t==0) return b;
	t /=d/2;
	if (t==2) return b+c;
	float p=d*(.3f*1.5f);
	float a=c;
	float s=p/4;

	if (t < 1) {
		float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
		return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
	}
	float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
	return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
}

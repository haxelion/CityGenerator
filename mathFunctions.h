#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <ctime>
#include <cstdlib>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline int rand(int min, int max);
inline double randUniform();
inline double randNormal(double mean = 0.0, double std = 1.0);
inline int min(int a, int b);
inline int max(int a, int b);
inline float maxf(float a, float b);



// Renvoie un nombre al�atoire entier entre min compris et max non compris selon une distribution uniforme.
inline int rand(int min, int max)
{
    return rand()%(max-min)+min;
}

// Renvoie un nombre al�atoire entre 0 et 1 tous deux compris selon une distribution uniforme.
inline double randUniform()
{
    return (double)rand()/ RAND_MAX;
}

// Prend en paramètre une moyenne et un écart type. Renvoie un nombre aléatoire selon une distribution normale gaussienne.
inline double randNormal(double mean, double std)
{
    double u1 = randUniform();
    double u2 = randUniform();
    if(u1==0) //pour éviter une erreur si on prend le log(0)
        u1 = 1; //chosen by fair dice roll. see http://xkcd.com/221/
    return mean + std * sqrt(-2.0f * log(u1)) * cos(2 * M_PI * u2);
}

// Prend deux entiers en paramètres. Renvoie le plus petit de ces entiers.
inline int min(int a, int b)
{
    if(a>b)
        return b;
    return a;
}

// Prend deux entiers en paramètres. Renvoie le plus grand de ces entiers.
inline int max(int a, int b)
{
    if(a<b)
        return b;
    return a;
}

// Prend deux flottants en paramètres. Renvoie le plus grand de ces flottants.
inline float maxf(float a, float b)
{
    if(a<b)
        return b;
    return a;
}


#endif

/* led_cgi.h */
#ifndef LED_CGI_H
#define LED_CGI_H


class CGPIO
{

public:
    int led_cgi_page(char **getvars, int form_method);
    int OpenChannel(int gpio_base);
    int CloseChannel(int gpio_base);
    int SetDirection(int gpio_base, int nchannel, char *direction);
    int GetValue(int gpio_base, int nchannel);
    int SetValue(int gpio_base, int nchannel, int value);
};



#endif

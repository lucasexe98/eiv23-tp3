#include <unity.h>
#include <soporte_placa.h>
void setUp(void){

}

void tearDown(void){

}
static void test_vacia (void){

}

int main (void){
    SP_init();
    SP_delay(500);
    UNITY_BEGIN();
    RUN_TEST (test_vacia);
    UNITY_END();
    return 0;
}
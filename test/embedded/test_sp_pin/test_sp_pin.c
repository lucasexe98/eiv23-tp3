#include <soporte_placa.h>
#include <unity.h>
#include <stm32f1xx.h>

/* CONSTANTES */

/**
 * @brief Registros del puerto GPIO donde se realizarán las pruebas
 * 
 */
#define GPIO_PRUEBA GPIOB


/**
 * @brief Máscara del bit de habilitación de reloj en el registro 
 * RCC->APB2ENR correspondiente a GPIO_PRUEBA
 * 
 */
#define RCC_APB2ENR_GPIO_PRUEBA_ENABLE RCC_APB2ENR_IOPBEN


/**
 * @brief Máscara del bit de reset en el registro RCC->APB2ENR
 * correspondiente a GPIO_PRUEBA
 * 
 */
#define RCC_APB2RSTR_GPIO_PRUEBA_RESET RCC_APB2RSTR_IOPBRST


/**
 * @brief Número de pin del pin de prueba
 * 
 */
#define PIN_PRUEBA 9


/**
 * @brief Handle del pin sobre el que se realizarán las pruebas
 * de configuración, lectura y escritura
 * 
 */
#define HPIN_PRUEBA SP_PB9


/**
 * @brief Registro de configuración correspondiente al pin
 * PIN_PRUEBA
 * 
 */
#define PIN_PRUEBA_CR (GPIO_PRUEBA->CRH)


/**
 * @brief Offset en el PIN_PRUEBA_CR donde se encuentra el
 * bit menos significativo de los cuatro bits de 
 * configuración del pin PIN_PRUEBA
 * 
 */
#define PIN_PRUEBA_CR_Pos GPIO_CRH_MODE9_Pos


/**
 * @brief Máscara correspondiente PIN_PRUEBA en el registro
 * de salida
 * 
 */
#define ODR_PIN_PRUEBA_Msk (1<<PIN_PRUEBA)
/**
 * @brief Máscara correspondiente PIN_PRUEBA en el registro
 * de entrada
 * 
 */
#define IDR_PIN_PRUEBA_Msk (1<<PIN_PRUEBA)


/**
 * @brief Máscara correspondiente al bit de reset de
 * PIN_PRUEBA en el registro BRR
 * 
 */
#define BRR_PIN_PRUEBA_Msk (1<<PIN_PRUEBA)


/**
 * @brief Máscara correspondiente al bit de set de
 * PIN_PRUEBA en el registro BSRR
 * 
 */
#define BSRR_SET_PIN_PRUEBA_Msk (1<<PIN_PRUEBA)


/**
 * @brief Máscara correspondiente al bit de reset de
 * PIN_PRUEBA en el registro BSRR
 * 
 */
#define BSRR_RESET_PIN_PRUEBA_Msk (1<<(PIN_PRUEBA+16))

void setUp(void){

}

void tearDown(void){

}

static void PRUEBA_SP_PinSetModo_EntradaFlotante(void){
    uint32_t ENTRADA_FLOTANTE = 0b0100;
    uint32_t CRL_ACTUAL = GPIOB->CRL ;
    uint32_t ODR_ACTUAL = GPIOB->ODR ;
    uint32_t CRH_ACTUAL = GPIOB->CRH ;
    SP_Pin_setModo(HPIN_PRUEBA , ENTRADA_FLOTANTE );
    uint32_t CRL_AFTER = GPIOB->CRL ;
    uint32_t ODR_AFTER = GPIOB->ODR ;
    uint32_t CRH_AFTER = GPIOB->CRH ;
    TEST_ASSERT_BITS_HIGH(0,CRL_ACTUAL ^ CRL_AFTER);
    TEST_ASSERT_BITS_HIGH(0,ODR_ACTUAL ^ ODR_AFTER);
    TEST_ASSERT_BITS_HIGH(0,CRH_ACTUAL ^ CRH_AFTER);
}

static void PRUEBA_SP_PinSetModo_ENTRADAPULL_UP_DOWN(void){
    uint32_t ENTRADA_PULLUP_PULLDOWN = 0b1000;
    uint32_t CRL_ACTUAL = GPIOB->CRL ;
    uint32_t ODR_ACTUAL = GPIOB->ODR ;
    uint32_t CRH_ACTUAL = GPIOB->CRH ;
    SP_Pin_setModo(HPIN_PRUEBA , ENTRADA_PULLUP_PULLDOWN );
    uint32_t CRL_AFTER = GPIOB->CRL ;
    uint32_t ODR_AFTER = GPIOB->ODR ;
    uint32_t CRH_AFTER = GPIOB->CRH ;
    TEST_ASSERT_BITS_HIGH(0,CRL_ACTUAL ^ CRL_AFTER);
    TEST_ASSERT_BITS_HIGH(0,ODR_ACTUAL ^ ODR_AFTER);
    TEST_ASSERT_BITS_HIGH(0,CRH_ACTUAL ^ CRH_AFTER);
}

static void PRUEBA_SP_PinSetModo_SALIDA_2MHz(void){
    uint32_t SALIDA_2MHz = 0b0010;
    uint32_t CRL_ACTUAL = GPIOB->CRL ;
    uint32_t ODR_ACTUAL = GPIOB->ODR ;
    uint32_t CRH_ACTUAL = GPIOB->CRH ;
    SP_Pin_setModo(HPIN_PRUEBA , SALIDA_2MHz );
    uint32_t CRL_AFTER = GPIOB->CRL ;
    uint32_t ODR_AFTER = GPIOB->ODR ;
    uint32_t CRH_AFTER = GPIOB->CRH ;
    TEST_ASSERT_BITS_HIGH(0,CRL_ACTUAL ^ CRL_AFTER);
    TEST_ASSERT_BITS_HIGH(0,ODR_ACTUAL ^ ODR_AFTER);
    TEST_ASSERT_BITS_HIGH(0,CRH_ACTUAL ^ CRH_AFTER);
}

static void PRUEBA_SP_PinSetModo_SALIDA_2MHz_OD(void){
    uint32_t SALIDA_2MHz_OPEN_DRAIN = 0b0110;
    uint32_t CRL_ACTUAL = GPIOB->CRL ;
    uint32_t ODR_ACTUAL = GPIOB->ODR ;
    uint32_t CRH_ACTUAL = GPIOB->CRH ;
    SP_Pin_setModo(HPIN_PRUEBA , SALIDA_2MHz_OPEN_DRAIN  );
    uint32_t CRL_AFTER = GPIOB->CRL ;
    uint32_t ODR_AFTER = GPIOB->ODR ;
    uint32_t CRH_AFTER = GPIOB->CRH ;
    TEST_ASSERT_BITS_HIGH(0,CRL_ACTUAL ^ CRL_AFTER);
    TEST_ASSERT_BITS_HIGH(0,ODR_ACTUAL ^ ODR_AFTER);
    TEST_ASSERT_BITS_HIGH(0,CRH_ACTUAL ^ CRH_AFTER);
}
int main (void){
    SP_init();
    SP_delay(500);
    UNITY_BEGIN();
    RUN_TEST (PRUEBA_SP_PinSetModo_EntradaFlotante);
    RUN_TEST (PRUEBA_SP_PinSetModo_ENTRADAPULL_UP_DOWN);
    RUN_TEST (PRUEBA_SP_PinSetModo_SALIDA_2MHz);
    RUN_TEST (PRUEBA_SP_PinSetModo_SALIDA_2MHz_OD);
//    RUN_TEST (test_SP_Pin_read__DEBE_retornar_TRUE_si_la_entrada_es_ALTA);
    UNITY_END();
    return 0;
}


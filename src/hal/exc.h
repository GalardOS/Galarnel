#ifndef HAL_EXC_H
#define HAL_EXC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*vector_handler)(long, long);

typedef struct exc_vector_table {
    vector_handler syn_handler;
    vector_handler irq_handler;
    vector_handler fiq_handler;
    vector_handler err_handler;
} exc_vector_table;

void exc_setup_vector(exc_vector_table handlers);

void exc_enable_syn();
void exc_disable_syn();

void exc_enable_irq();
void exc_disable_irq();

void exc_enable_firq();
void exc_disable_firq();

void exc_enable_err();
void exc_disable_err();

#ifdef __cplusplus
}
#endif

#endif // HAL_EXC_H
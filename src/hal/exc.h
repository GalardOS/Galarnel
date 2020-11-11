#ifndef HAL_EXC_H
#define HAL_EXC_H

extern "C" {

    typedef void(*vector_handler)(long, long);

    typedef struct {
        vector_handler syn_handler;
        vector_handler irq_handler;
        vector_handler fiq_handler;
        vector_handler err_handler;
    } vector_table;

    void exc_setup_vector(vector_table handlers);

    void exc_enable_syn();
    void exc_disable_syn();

    void exc_enable_irq();
    void exc_disable_irq();

    void exc_enable_firq();
    void exc_disable_firq();

    void exc_enable_err();
    void exc_disable_err();
}

#endif // HAL_EXC_H
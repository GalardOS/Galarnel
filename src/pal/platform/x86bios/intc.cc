#include "pal/intc.hh"

#include "pal/drivers/pic/pic.hh"

namespace pal { namespace intc {

    void initialize() {
        pic::initialize();
    }

    handler_id add_handler(const irq_handler_descriptor& descriptor) {

        // Setup the pic interrupt descriptor from the 
        // generic interrupt descriptor.
        pic::int_descriptor pic_descriptor;
        
        // Disable interrupts while this irq is being handled
        pic_descriptor.descriptor_type = pic::desc_type::interrupt; 

        // Set the interrupt id to the IDT interrupt number
        pic_descriptor.int_number = descriptor.irqid;

        // Set the priviledge level to jump when irq to kernel mode
        pic_descriptor.priviledge_level = 0;

        // Set the irq handler
        pic_descriptor.handler = descriptor.handler;

        // Add the descriptor to an IDT entry
        pic::set_entry(pic_descriptor);
    }

    void remove_handler(irq_handler_descriptor descriptor) {
        pic::set_ignore_entry(descriptor.irqid);
    }

    void add_error_handler(void(*error_handler)(reason)) {

    }

} }
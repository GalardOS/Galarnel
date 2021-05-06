extern void main(int argc, char** argv);

typedef void (*ctor)();
extern "C" ctor start_ctors;
extern "C" ctor end_ctors;

namespace steel {
    void __event_initialize();
}

extern "C" 
void gimme_all_your_lovin(void)
{
    steel::__event_initialize();

    // Call all global constructors
    for(ctor* constructor = &start_ctors; constructor != &end_ctors; constructor++) {
        (*constructor)();
    }

    // No command line arguments are passed right now. This should be read from the 
    // configuration file on the boot drive.
    main(0, nullptr);

    while(true);
}

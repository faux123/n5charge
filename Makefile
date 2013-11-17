obj-m := n5charge.o
n5charge-objs := compat.o hook.o main.o my_bq24192_charger.o

all: modules

modules:
	make -C $(KERNEL_SOURCES) M=$(PWD) modules
clean:
	make -C $(KERNEL_SOURCES) M=$(PWD) clean
	rm -vf *.ko *.o

hook.o: hook.h mm_ksyms.h
main.o: hook.h my_bq24192_charger.h
my_bq24192_charger.o: bq24192_charger_ksyms.h my_bq24192_charger.h

.PHONY: modules clean

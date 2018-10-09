default_target: all

.PHONY: default_target

ifeq ($(DEBUG),1)
  BUILD_TYPE = -DCMAKE_BUILD_TYPE=Debug
endif

all: build-target/Makefile
	$(MAKE) -C build-target

.PHONY: all

build-target/Makefile: Makefile CMakeLists.txt
	cmake -H. -Bbuild-target -DCMAKE_TOOLCHAIN_FILE=sdcc.cmake $(BUILD_TYPE)

clean:
	rm -rf build-target

.PHONY: clean

flash: all
	sudo stm8flash -c stlinkv2 -p stm8s103?3 -w build-target/src/sensor.ihx

.PHONY: flash

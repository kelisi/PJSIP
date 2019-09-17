# build/os-auto.mak.  Generated from os-auto.mak.in by configure.

export OS_CFLAGS   := $(CC_DEF)PJ_AUTOCONF=1  -O3 -DNDEBUG -msoft-float -fno-builtin -g -DPJ_IS_BIG_ENDIAN=0 -DPJ_IS_LITTLE_ENDIAN=1

export OS_CXXFLAGS := $(CC_DEF)PJ_AUTOCONF=1 -g

export OS_LDFLAGS  :=   -lopus -lssl -lcrypto -lopenh264 -lstdc++ -lm -lpthread  -framework CoreAudio -framework CoreServices -framework AudioUnit -framework AudioToolbox -framework Foundation -framework AppKit -framework AVFoundation -framework CoreGraphics -framework QuartzCore -framework CoreVideo -framework CoreMedia -framework VideoToolbox -L/usr/local/lib -lSDL2  -L/usr/local/Cellar/ffmpeg/4.1.4_1/lib -lavdevice -lavformat -lavcodec -lswscale -lavutil -L/usr/local/Cellar/gnutls/3.6.9/lib -lgnutls -lopencore-amrnb -lopencore-amrwb

export OS_SOURCES  := 



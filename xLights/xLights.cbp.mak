#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.138                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  -DwxUSE_UNICODE
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUGLINUX =  $(INC)
CFLAGS_DEBUGLINUX =  $(CFLAGS) -Wall -g `wx-config --cflags` -Winvalid-pch -DWX_PRECOMP -D__WXDEBUG__
RESINC_DEBUGLINUX =  $(RESINC)
RCFLAGS_DEBUGLINUX =  $(RCFLAGS)
LIBDIR_DEBUGLINUX =  $(LIBDIR)
LIB_DEBUGLINUX = $(LIB)
LDFLAGS_DEBUGLINUX =  `wx-config --libs std,media` $(LDFLAGS)
OBJDIR_DEBUGLINUX = .objs
DEP_DEBUGLINUX = 
OUT_DEBUGLINUX = ../bin/xLights

INC_RELEASELINUX =  $(INC)
CFLAGS_RELEASELINUX =  $(CFLAGS) -O2 -Wall `wx-config --version=2.9 --cflags` -Winvalid-pch -DWX_PRECOMP -DNDEBUG
RESINC_RELEASELINUX =  $(RESINC)
RCFLAGS_RELEASELINUX =  $(RCFLAGS)
LIBDIR_RELEASELINUX =  $(LIBDIR)
LIB_RELEASELINUX = $(LIB)
LDFLAGS_RELEASELINUX =  -s `wx-config --version=2.9 --libs std,media` $(LDFLAGS)
OBJDIR_RELEASELINUX = .objs
DEP_RELEASELINUX = 
OUT_RELEASELINUX = ../bin/xLights

OBJ_DEBUGLINUX = $(OBJDIR_DEBUGLINUX)/SerialPortWithRate.o $(OBJDIR_DEBUGLINUX)/serial.o $(OBJDIR_DEBUGLINUX)/ShowDatesDialog.o $(OBJDIR_DEBUGLINUX)/SeqParmsDialog.o $(OBJDIR_DEBUGLINUX)/SeqOpenDialog.o $(OBJDIR_DEBUGLINUX)/SeqExportDialog.o $(OBJDIR_DEBUGLINUX)/SeqElementMismatchDialog.o $(OBJDIR_DEBUGLINUX)/xlights_out.o $(OBJDIR_DEBUGLINUX)/xLightsMain.o $(OBJDIR_DEBUGLINUX)/xLightsApp.o $(OBJDIR_DEBUGLINUX)/RgbEffects.o $(OBJDIR_DEBUGLINUX)/ModelClass.o $(OBJDIR_DEBUGLINUX)/PixelBuffer.o $(OBJDIR_DEBUGLINUX)/PaletteMgmtDialog.o $(OBJDIR_DEBUGLINUX)/NetInfo.o $(OBJDIR_DEBUGLINUX)/ModelListDialog.o $(OBJDIR_DEBUGLINUX)/ModelDialog.o $(OBJDIR_DEBUGLINUX)/EffectListDialog.o $(OBJDIR_DEBUGLINUX)/E131Dialog.o $(OBJDIR_DEBUGLINUX)/ChannelMapDialog.o $(OBJDIR_DEBUGLINUX)/ChannelLayoutDialog.o $(OBJDIR_DEBUGLINUX)/RenderLife.o $(OBJDIR_DEBUGLINUX)/RenderTwinkle.o $(OBJDIR_DEBUGLINUX)/RenderTree.o $(OBJDIR_DEBUGLINUX)/RenderText.o $(OBJDIR_DEBUGLINUX)/RenderSpirograph.o $(OBJDIR_DEBUGLINUX)/RenderSpirals.o $(OBJDIR_DEBUGLINUX)/RenderSnowstorm.o $(OBJDIR_DEBUGLINUX)/RenderSnowflakes.o $(OBJDIR_DEBUGLINUX)/RenderSean.o $(OBJDIR_DEBUGLINUX)/RenderPictures.o $(OBJDIR_DEBUGLINUX)/RenderMeteors.o $(OBJDIR_DEBUGLINUX)/AddShowDialog.o $(OBJDIR_DEBUGLINUX)/RenderGarlands.o $(OBJDIR_DEBUGLINUX)/RenderFire.o $(OBJDIR_DEBUGLINUX)/RenderColorWash.o $(OBJDIR_DEBUGLINUX)/RenderButterfly.o $(OBJDIR_DEBUGLINUX)/RenderBars.o $(OBJDIR_DEBUGLINUX)/PlayerFrame.o $(OBJDIR_DEBUGLINUX)/PlaybackOptionsDialog.o

OBJ_RELEASELINUX = $(OBJDIR_RELEASELINUX)/SerialPortWithRate.o $(OBJDIR_RELEASELINUX)/serial.o $(OBJDIR_RELEASELINUX)/ShowDatesDialog.o $(OBJDIR_RELEASELINUX)/SeqParmsDialog.o $(OBJDIR_RELEASELINUX)/SeqOpenDialog.o $(OBJDIR_RELEASELINUX)/SeqExportDialog.o $(OBJDIR_RELEASELINUX)/SeqElementMismatchDialog.o $(OBJDIR_RELEASELINUX)/xlights_out.o $(OBJDIR_RELEASELINUX)/xLightsMain.o $(OBJDIR_RELEASELINUX)/xLightsApp.o $(OBJDIR_RELEASELINUX)/RgbEffects.o $(OBJDIR_RELEASELINUX)/ModelClass.o $(OBJDIR_RELEASELINUX)/PixelBuffer.o $(OBJDIR_RELEASELINUX)/PaletteMgmtDialog.o $(OBJDIR_RELEASELINUX)/NetInfo.o $(OBJDIR_RELEASELINUX)/ModelListDialog.o $(OBJDIR_RELEASELINUX)/ModelDialog.o $(OBJDIR_RELEASELINUX)/EffectListDialog.o $(OBJDIR_RELEASELINUX)/E131Dialog.o $(OBJDIR_RELEASELINUX)/ChannelMapDialog.o $(OBJDIR_RELEASELINUX)/ChannelLayoutDialog.o $(OBJDIR_RELEASELINUX)/RenderLife.o $(OBJDIR_RELEASELINUX)/RenderTwinkle.o $(OBJDIR_RELEASELINUX)/RenderTree.o $(OBJDIR_RELEASELINUX)/RenderText.o $(OBJDIR_RELEASELINUX)/RenderSpirograph.o $(OBJDIR_RELEASELINUX)/RenderSpirals.o $(OBJDIR_RELEASELINUX)/RenderSnowstorm.o $(OBJDIR_RELEASELINUX)/RenderSnowflakes.o $(OBJDIR_RELEASELINUX)/RenderSean.o $(OBJDIR_RELEASELINUX)/RenderPictures.o $(OBJDIR_RELEASELINUX)/RenderMeteors.o $(OBJDIR_RELEASELINUX)/AddShowDialog.o $(OBJDIR_RELEASELINUX)/RenderGarlands.o $(OBJDIR_RELEASELINUX)/RenderFire.o $(OBJDIR_RELEASELINUX)/RenderColorWash.o $(OBJDIR_RELEASELINUX)/RenderButterfly.o $(OBJDIR_RELEASELINUX)/RenderBars.o $(OBJDIR_RELEASELINUX)/PlayerFrame.o $(OBJDIR_RELEASELINUX)/PlaybackOptionsDialog.o

all: debuglinux releaselinux

clean: clean_debuglinux clean_releaselinux

before_debuglinux: 
	test -d ../bin || mkdir -p ../bin
	test -d $(OBJDIR_DEBUGLINUX) || mkdir -p $(OBJDIR_DEBUGLINUX)

after_debuglinux: 

debuglinux: before_debuglinux out_debuglinux after_debuglinux

out_debuglinux: before_debuglinux $(OBJ_DEBUGLINUX) $(DEP_DEBUGLINUX)
	$(LD) $(LIBDIR_DEBUGLINUX) -o $(OUT_DEBUGLINUX) $(OBJ_DEBUGLINUX)  $(LDFLAGS_DEBUGLINUX) $(LIB_DEBUGLINUX)

$(OBJDIR_DEBUGLINUX)/SerialPortWithRate.o: SerialPortWithRate.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c SerialPortWithRate.cpp -o $(OBJDIR_DEBUGLINUX)/SerialPortWithRate.o

$(OBJDIR_DEBUGLINUX)/serial.o: serial.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c serial.cpp -o $(OBJDIR_DEBUGLINUX)/serial.o

$(OBJDIR_DEBUGLINUX)/ShowDatesDialog.o: ShowDatesDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c ShowDatesDialog.cpp -o $(OBJDIR_DEBUGLINUX)/ShowDatesDialog.o

$(OBJDIR_DEBUGLINUX)/SeqParmsDialog.o: SeqParmsDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c SeqParmsDialog.cpp -o $(OBJDIR_DEBUGLINUX)/SeqParmsDialog.o

$(OBJDIR_DEBUGLINUX)/SeqOpenDialog.o: SeqOpenDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c SeqOpenDialog.cpp -o $(OBJDIR_DEBUGLINUX)/SeqOpenDialog.o

$(OBJDIR_DEBUGLINUX)/SeqExportDialog.o: SeqExportDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c SeqExportDialog.cpp -o $(OBJDIR_DEBUGLINUX)/SeqExportDialog.o

$(OBJDIR_DEBUGLINUX)/SeqElementMismatchDialog.o: SeqElementMismatchDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c SeqElementMismatchDialog.cpp -o $(OBJDIR_DEBUGLINUX)/SeqElementMismatchDialog.o

$(OBJDIR_DEBUGLINUX)/xlights_out.o: xlights_out.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c xlights_out.cpp -o $(OBJDIR_DEBUGLINUX)/xlights_out.o

$(OBJDIR_DEBUGLINUX)/xLightsMain.o: xLightsMain.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c xLightsMain.cpp -o $(OBJDIR_DEBUGLINUX)/xLightsMain.o

$(OBJDIR_DEBUGLINUX)/xLightsApp.o: xLightsApp.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c xLightsApp.cpp -o $(OBJDIR_DEBUGLINUX)/xLightsApp.o

$(OBJDIR_DEBUGLINUX)/RgbEffects.o: RgbEffects.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RgbEffects.cpp -o $(OBJDIR_DEBUGLINUX)/RgbEffects.o

$(OBJDIR_DEBUGLINUX)/ModelClass.o: ModelClass.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c ModelClass.cpp -o $(OBJDIR_DEBUGLINUX)/ModelClass.o

$(OBJDIR_DEBUGLINUX)/PixelBuffer.o: PixelBuffer.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c PixelBuffer.cpp -o $(OBJDIR_DEBUGLINUX)/PixelBuffer.o

$(OBJDIR_DEBUGLINUX)/PaletteMgmtDialog.o: PaletteMgmtDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c PaletteMgmtDialog.cpp -o $(OBJDIR_DEBUGLINUX)/PaletteMgmtDialog.o

$(OBJDIR_DEBUGLINUX)/NetInfo.o: NetInfo.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c NetInfo.cpp -o $(OBJDIR_DEBUGLINUX)/NetInfo.o

$(OBJDIR_DEBUGLINUX)/ModelListDialog.o: ModelListDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c ModelListDialog.cpp -o $(OBJDIR_DEBUGLINUX)/ModelListDialog.o

$(OBJDIR_DEBUGLINUX)/ModelDialog.o: ModelDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c ModelDialog.cpp -o $(OBJDIR_DEBUGLINUX)/ModelDialog.o

$(OBJDIR_DEBUGLINUX)/EffectListDialog.o: EffectListDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c EffectListDialog.cpp -o $(OBJDIR_DEBUGLINUX)/EffectListDialog.o

$(OBJDIR_DEBUGLINUX)/E131Dialog.o: E131Dialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c E131Dialog.cpp -o $(OBJDIR_DEBUGLINUX)/E131Dialog.o

$(OBJDIR_DEBUGLINUX)/ChannelMapDialog.o: ChannelMapDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c ChannelMapDialog.cpp -o $(OBJDIR_DEBUGLINUX)/ChannelMapDialog.o

$(OBJDIR_DEBUGLINUX)/ChannelLayoutDialog.o: ChannelLayoutDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c ChannelLayoutDialog.cpp -o $(OBJDIR_DEBUGLINUX)/ChannelLayoutDialog.o

$(OBJDIR_DEBUGLINUX)/RenderLife.o: RenderLife.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderLife.cpp -o $(OBJDIR_DEBUGLINUX)/RenderLife.o

$(OBJDIR_DEBUGLINUX)/RenderTwinkle.o: RenderTwinkle.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderTwinkle.cpp -o $(OBJDIR_DEBUGLINUX)/RenderTwinkle.o

$(OBJDIR_DEBUGLINUX)/RenderTree.o: RenderTree.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderTree.cpp -o $(OBJDIR_DEBUGLINUX)/RenderTree.o

$(OBJDIR_DEBUGLINUX)/RenderText.o: RenderText.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderText.cpp -o $(OBJDIR_DEBUGLINUX)/RenderText.o

$(OBJDIR_DEBUGLINUX)/RenderSpirograph.o: RenderSpirograph.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderSpirograph.cpp -o $(OBJDIR_DEBUGLINUX)/RenderSpirograph.o

$(OBJDIR_DEBUGLINUX)/RenderSpirals.o: RenderSpirals.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderSpirals.cpp -o $(OBJDIR_DEBUGLINUX)/RenderSpirals.o

$(OBJDIR_DEBUGLINUX)/RenderSnowstorm.o: RenderSnowstorm.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderSnowstorm.cpp -o $(OBJDIR_DEBUGLINUX)/RenderSnowstorm.o

$(OBJDIR_DEBUGLINUX)/RenderSnowflakes.o: RenderSnowflakes.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderSnowflakes.cpp -o $(OBJDIR_DEBUGLINUX)/RenderSnowflakes.o

$(OBJDIR_DEBUGLINUX)/RenderSean.o: RenderSean.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderSean.cpp -o $(OBJDIR_DEBUGLINUX)/RenderSean.o

$(OBJDIR_DEBUGLINUX)/RenderPictures.o: RenderPictures.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderPictures.cpp -o $(OBJDIR_DEBUGLINUX)/RenderPictures.o

$(OBJDIR_DEBUGLINUX)/RenderMeteors.o: RenderMeteors.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderMeteors.cpp -o $(OBJDIR_DEBUGLINUX)/RenderMeteors.o

$(OBJDIR_DEBUGLINUX)/AddShowDialog.o: AddShowDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c AddShowDialog.cpp -o $(OBJDIR_DEBUGLINUX)/AddShowDialog.o

$(OBJDIR_DEBUGLINUX)/RenderGarlands.o: RenderGarlands.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderGarlands.cpp -o $(OBJDIR_DEBUGLINUX)/RenderGarlands.o

$(OBJDIR_DEBUGLINUX)/RenderFire.o: RenderFire.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderFire.cpp -o $(OBJDIR_DEBUGLINUX)/RenderFire.o

$(OBJDIR_DEBUGLINUX)/RenderColorWash.o: RenderColorWash.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderColorWash.cpp -o $(OBJDIR_DEBUGLINUX)/RenderColorWash.o

$(OBJDIR_DEBUGLINUX)/RenderButterfly.o: RenderButterfly.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderButterfly.cpp -o $(OBJDIR_DEBUGLINUX)/RenderButterfly.o

$(OBJDIR_DEBUGLINUX)/RenderBars.o: RenderBars.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c RenderBars.cpp -o $(OBJDIR_DEBUGLINUX)/RenderBars.o

$(OBJDIR_DEBUGLINUX)/PlayerFrame.o: PlayerFrame.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c PlayerFrame.cpp -o $(OBJDIR_DEBUGLINUX)/PlayerFrame.o

$(OBJDIR_DEBUGLINUX)/PlaybackOptionsDialog.o: PlaybackOptionsDialog.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX) $(INC_DEBUGLINUX) -c PlaybackOptionsDialog.cpp -o $(OBJDIR_DEBUGLINUX)/PlaybackOptionsDialog.o

clean_debuglinux: 
	rm -f $(OBJ_DEBUGLINUX) $(OUT_DEBUGLINUX)

before_releaselinux: 
	test -d ../bin || mkdir -p ../bin
	test -d $(OBJDIR_RELEASELINUX) || mkdir -p $(OBJDIR_RELEASELINUX)

after_releaselinux: 

releaselinux: before_releaselinux out_releaselinux after_releaselinux

out_releaselinux: before_releaselinux $(OBJ_RELEASELINUX) $(DEP_RELEASELINUX)
	$(LD) $(LIBDIR_RELEASELINUX) -o $(OUT_RELEASELINUX) $(OBJ_RELEASELINUX)  $(LDFLAGS_RELEASELINUX) $(LIB_RELEASELINUX)

$(OBJDIR_RELEASELINUX)/SerialPortWithRate.o: SerialPortWithRate.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c SerialPortWithRate.cpp -o $(OBJDIR_RELEASELINUX)/SerialPortWithRate.o

$(OBJDIR_RELEASELINUX)/serial.o: serial.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c serial.cpp -o $(OBJDIR_RELEASELINUX)/serial.o

$(OBJDIR_RELEASELINUX)/ShowDatesDialog.o: ShowDatesDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c ShowDatesDialog.cpp -o $(OBJDIR_RELEASELINUX)/ShowDatesDialog.o

$(OBJDIR_RELEASELINUX)/SeqParmsDialog.o: SeqParmsDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c SeqParmsDialog.cpp -o $(OBJDIR_RELEASELINUX)/SeqParmsDialog.o

$(OBJDIR_RELEASELINUX)/SeqOpenDialog.o: SeqOpenDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c SeqOpenDialog.cpp -o $(OBJDIR_RELEASELINUX)/SeqOpenDialog.o

$(OBJDIR_RELEASELINUX)/SeqExportDialog.o: SeqExportDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c SeqExportDialog.cpp -o $(OBJDIR_RELEASELINUX)/SeqExportDialog.o

$(OBJDIR_RELEASELINUX)/SeqElementMismatchDialog.o: SeqElementMismatchDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c SeqElementMismatchDialog.cpp -o $(OBJDIR_RELEASELINUX)/SeqElementMismatchDialog.o

$(OBJDIR_RELEASELINUX)/xlights_out.o: xlights_out.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c xlights_out.cpp -o $(OBJDIR_RELEASELINUX)/xlights_out.o

$(OBJDIR_RELEASELINUX)/xLightsMain.o: xLightsMain.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c xLightsMain.cpp -o $(OBJDIR_RELEASELINUX)/xLightsMain.o

$(OBJDIR_RELEASELINUX)/xLightsApp.o: xLightsApp.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c xLightsApp.cpp -o $(OBJDIR_RELEASELINUX)/xLightsApp.o

$(OBJDIR_RELEASELINUX)/RgbEffects.o: RgbEffects.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RgbEffects.cpp -o $(OBJDIR_RELEASELINUX)/RgbEffects.o

$(OBJDIR_RELEASELINUX)/ModelClass.o: ModelClass.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c ModelClass.cpp -o $(OBJDIR_RELEASELINUX)/ModelClass.o

$(OBJDIR_RELEASELINUX)/PixelBuffer.o: PixelBuffer.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c PixelBuffer.cpp -o $(OBJDIR_RELEASELINUX)/PixelBuffer.o

$(OBJDIR_RELEASELINUX)/PaletteMgmtDialog.o: PaletteMgmtDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c PaletteMgmtDialog.cpp -o $(OBJDIR_RELEASELINUX)/PaletteMgmtDialog.o

$(OBJDIR_RELEASELINUX)/NetInfo.o: NetInfo.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c NetInfo.cpp -o $(OBJDIR_RELEASELINUX)/NetInfo.o

$(OBJDIR_RELEASELINUX)/ModelListDialog.o: ModelListDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c ModelListDialog.cpp -o $(OBJDIR_RELEASELINUX)/ModelListDialog.o

$(OBJDIR_RELEASELINUX)/ModelDialog.o: ModelDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c ModelDialog.cpp -o $(OBJDIR_RELEASELINUX)/ModelDialog.o

$(OBJDIR_RELEASELINUX)/EffectListDialog.o: EffectListDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c EffectListDialog.cpp -o $(OBJDIR_RELEASELINUX)/EffectListDialog.o

$(OBJDIR_RELEASELINUX)/E131Dialog.o: E131Dialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c E131Dialog.cpp -o $(OBJDIR_RELEASELINUX)/E131Dialog.o

$(OBJDIR_RELEASELINUX)/ChannelMapDialog.o: ChannelMapDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c ChannelMapDialog.cpp -o $(OBJDIR_RELEASELINUX)/ChannelMapDialog.o

$(OBJDIR_RELEASELINUX)/ChannelLayoutDialog.o: ChannelLayoutDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c ChannelLayoutDialog.cpp -o $(OBJDIR_RELEASELINUX)/ChannelLayoutDialog.o

$(OBJDIR_RELEASELINUX)/RenderLife.o: RenderLife.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderLife.cpp -o $(OBJDIR_RELEASELINUX)/RenderLife.o

$(OBJDIR_RELEASELINUX)/RenderTwinkle.o: RenderTwinkle.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderTwinkle.cpp -o $(OBJDIR_RELEASELINUX)/RenderTwinkle.o

$(OBJDIR_RELEASELINUX)/RenderTree.o: RenderTree.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderTree.cpp -o $(OBJDIR_RELEASELINUX)/RenderTree.o

$(OBJDIR_RELEASELINUX)/RenderText.o: RenderText.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderText.cpp -o $(OBJDIR_RELEASELINUX)/RenderText.o

$(OBJDIR_RELEASELINUX)/RenderSpirograph.o: RenderSpirograph.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderSpirograph.cpp -o $(OBJDIR_RELEASELINUX)/RenderSpirograph.o

$(OBJDIR_RELEASELINUX)/RenderSpirals.o: RenderSpirals.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderSpirals.cpp -o $(OBJDIR_RELEASELINUX)/RenderSpirals.o

$(OBJDIR_RELEASELINUX)/RenderSnowstorm.o: RenderSnowstorm.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderSnowstorm.cpp -o $(OBJDIR_RELEASELINUX)/RenderSnowstorm.o

$(OBJDIR_RELEASELINUX)/RenderSnowflakes.o: RenderSnowflakes.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderSnowflakes.cpp -o $(OBJDIR_RELEASELINUX)/RenderSnowflakes.o

$(OBJDIR_RELEASELINUX)/RenderSean.o: RenderSean.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderSean.cpp -o $(OBJDIR_RELEASELINUX)/RenderSean.o

$(OBJDIR_RELEASELINUX)/RenderPictures.o: RenderPictures.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderPictures.cpp -o $(OBJDIR_RELEASELINUX)/RenderPictures.o

$(OBJDIR_RELEASELINUX)/RenderMeteors.o: RenderMeteors.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderMeteors.cpp -o $(OBJDIR_RELEASELINUX)/RenderMeteors.o

$(OBJDIR_RELEASELINUX)/AddShowDialog.o: AddShowDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c AddShowDialog.cpp -o $(OBJDIR_RELEASELINUX)/AddShowDialog.o

$(OBJDIR_RELEASELINUX)/RenderGarlands.o: RenderGarlands.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderGarlands.cpp -o $(OBJDIR_RELEASELINUX)/RenderGarlands.o

$(OBJDIR_RELEASELINUX)/RenderFire.o: RenderFire.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderFire.cpp -o $(OBJDIR_RELEASELINUX)/RenderFire.o

$(OBJDIR_RELEASELINUX)/RenderColorWash.o: RenderColorWash.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderColorWash.cpp -o $(OBJDIR_RELEASELINUX)/RenderColorWash.o

$(OBJDIR_RELEASELINUX)/RenderButterfly.o: RenderButterfly.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderButterfly.cpp -o $(OBJDIR_RELEASELINUX)/RenderButterfly.o

$(OBJDIR_RELEASELINUX)/RenderBars.o: RenderBars.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c RenderBars.cpp -o $(OBJDIR_RELEASELINUX)/RenderBars.o

$(OBJDIR_RELEASELINUX)/PlayerFrame.o: PlayerFrame.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c PlayerFrame.cpp -o $(OBJDIR_RELEASELINUX)/PlayerFrame.o

$(OBJDIR_RELEASELINUX)/PlaybackOptionsDialog.o: PlaybackOptionsDialog.cpp
	$(CXX) $(CFLAGS_RELEASELINUX) $(INC_RELEASELINUX) -c PlaybackOptionsDialog.cpp -o $(OBJDIR_RELEASELINUX)/PlaybackOptionsDialog.o

clean_releaselinux: 
	rm -f $(OBJ_RELEASELINUX) $(OUT_RELEASELINUX)

SerialPortWithRate.cpp: SerialPortWithRate.h

serial.cpp: serial.h serial_win32.cpp serial_osx.cpp serial_posix.cpp

serial_posix.cpp: serial.h

ShowDatesDialog.cpp: ShowDatesDialog.h

SeqParmsDialog.cpp: SeqParmsDialog.h

SeqOpenDialog.cpp: SeqOpenDialog.h

SeqExportDialog.cpp: SeqExportDialog.h

SeqElementMismatchDialog.cpp: SeqElementMismatchDialog.h

xlights_out.cpp: xlights_out.h serial.h

xLightsMain.cpp: xLightsMain.h SerialPortWithRate.h E131Dialog.h xLightsBasic.cpp TabSetup.cpp TabTest.cpp TabConvert.cpp TabSchedule.cpp TabSequence.cpp

xLightsMain.h: xlights_out.h PlayerFrame.h AddShowDialog.h ShowDatesDialog.h PlaybackOptionsDialog.h ModelListDialog.h EffectListDialog.h PaletteMgmtDialog.h SeqParmsDialog.h ChannelMapDialog.h SeqOpenDialog.h SeqExportDialog.h SeqElementMismatchDialog.h PixelBuffer.h NetInfo.h

ModelListDialog.h: ModelClass.h

ChannelMapDialog.h: NetInfo.h

PixelBuffer.h: ModelClass.h RgbEffects.h

xLightsBasic.cpp: serial.h

xLightsApp.cpp: xLightsApp.h xLightsMain.h

RgbEffects.cpp: RgbEffects.h

ModelClass.cpp: ModelClass.h

PixelBuffer.cpp: PixelBuffer.h

PaletteMgmtDialog.cpp: PaletteMgmtDialog.h

NetInfo.cpp: NetInfo.h

ModelListDialog.cpp: ModelListDialog.h ModelDialog.h ChannelLayoutDialog.h

ModelDialog.cpp: ModelDialog.h

EffectListDialog.cpp: EffectListDialog.h

E131Dialog.cpp: E131Dialog.h

ChannelMapDialog.cpp: ChannelMapDialog.h

ChannelLayoutDialog.cpp: ChannelLayoutDialog.h

RenderLife.cpp: RgbEffects.h

RenderTwinkle.cpp: RgbEffects.h

RenderTree.cpp: RgbEffects.h

RenderText.cpp: RgbEffects.h

RenderSpirograph.cpp: RgbEffects.h

RenderSpirals.cpp: RgbEffects.h

RenderSnowstorm.cpp: RgbEffects.h

RenderSnowflakes.cpp: RgbEffects.h

RenderSean.cpp: RgbEffects.h

RenderPictures.cpp: RgbEffects.h

RenderMeteors.cpp: RgbEffects.h

AddShowDialog.cpp: AddShowDialog.h

RenderGarlands.cpp: RgbEffects.h

RenderFire.cpp: RgbEffects.h

RenderColorWash.cpp: RgbEffects.h

RenderButterfly.cpp: RgbEffects.h

RenderBars.cpp: RgbEffects.h

PlayerFrame.cpp: PlayerFrame.h

PlaybackOptionsDialog.cpp: PlaybackOptionsDialog.h

.PHONY: before_debuglinux after_debuglinux clean_debuglinux before_releaselinux after_releaselinux clean_releaselinux


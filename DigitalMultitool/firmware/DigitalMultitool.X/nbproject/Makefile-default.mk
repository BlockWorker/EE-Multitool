#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/display/FT8_commands.c ../src/math/expression.c ../src/math/expr_tokens.c ../src/math/list64.c ../src/math/tuplestack.c ../src/math/vars.c ../src/math/mathext.c ../src/peripherals/keyboard.c ../src/system_config/default/framework/driver/adc/src/drv_adc_static.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S ../src/system_config/default/framework/system/memory/ebi/src/sys_memory_ebi_static.c ../src/system_config/default/framework/system/memory/src/sys_memory_static.c ../src/system_config/default/framework/system/ports/src/sys_ports_static.c ../src/system_config/default/framework/system/rtcc/sys_rtcc.c ../src/system_config/default/system_init.c ../src/system_config/default/system_interrupt.c ../src/system_config/default/system_exceptions.c ../src/system_config/default/system_tasks.c ../src/app.c ../src/main.c ../../../../framework/driver/i2c/src/dynamic/drv_i2c.c ../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c ../src/framework/driver/sram/src/dynamic/drv_sram.c ../../../../framework/driver/tmr/src/dynamic/drv_tmr.c ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c ../../../../framework/system/console/src/sys_console.c ../../../../framework/system/console/src/sys_console_usb_cdc.c ../../../../framework/system/debug/src/sys_debug.c ../../../../framework/system/fs/src/dynamic/sys_fs.c ../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c ../../../../framework/system/fs/fat_fs/src/file_system/ff.c ../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c ../../../../framework/system/int/src/sys_int_pic32.c ../../../../framework/system/random/src/sys_random.c ../../../../framework/system/tmr/src/sys_tmr.c ../../../../framework/usb/src/dynamic/usb_device.c ../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1390850504/FT8_commands.o ${OBJECTDIR}/_ext/1019118654/expression.o ${OBJECTDIR}/_ext/1019118654/expr_tokens.o ${OBJECTDIR}/_ext/1019118654/list64.o ${OBJECTDIR}/_ext/1019118654/tuplestack.o ${OBJECTDIR}/_ext/1019118654/vars.o ${OBJECTDIR}/_ext/1019118654/mathext.o ${OBJECTDIR}/_ext/705376131/keyboard.o ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o ${OBJECTDIR}/_ext/715571337/drv_spi_static.o ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ${OBJECTDIR}/_ext/476726740/sys_rtcc.o ${OBJECTDIR}/_ext/1688732426/system_init.o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/280795049/drv_i2c.o ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o ${OBJECTDIR}/_ext/1868400972/drv_sram.o ${OBJECTDIR}/_ext/185269848/drv_tmr.o ${OBJECTDIR}/_ext/246898221/drv_usbhs.o ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o ${OBJECTDIR}/_ext/30809027/sys_console.o ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o ${OBJECTDIR}/_ext/1408546951/sys_debug.o ${OBJECTDIR}/_ext/2104899551/sys_fs.o ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o ${OBJECTDIR}/_ext/66287330/ff.o ${OBJECTDIR}/_ext/2072869785/diskio.o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ${OBJECTDIR}/_ext/1283840359/sys_random.o ${OBJECTDIR}/_ext/1264926591/sys_tmr.o ${OBJECTDIR}/_ext/610166344/usb_device.o ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1390850504/FT8_commands.o.d ${OBJECTDIR}/_ext/1019118654/expression.o.d ${OBJECTDIR}/_ext/1019118654/expr_tokens.o.d ${OBJECTDIR}/_ext/1019118654/list64.o.d ${OBJECTDIR}/_ext/1019118654/tuplestack.o.d ${OBJECTDIR}/_ext/1019118654/vars.o.d ${OBJECTDIR}/_ext/1019118654/mathext.o.d ${OBJECTDIR}/_ext/705376131/keyboard.o.d ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o.d ${OBJECTDIR}/_ext/715571337/drv_spi_static.o.d ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o.d ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o.d ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o.d ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o.d ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o.d ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o.d ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d ${OBJECTDIR}/_ext/476726740/sys_rtcc.o.d ${OBJECTDIR}/_ext/1688732426/system_init.o.d ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d ${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/280795049/drv_i2c.o.d ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o.d ${OBJECTDIR}/_ext/1868400972/drv_sram.o.d ${OBJECTDIR}/_ext/185269848/drv_tmr.o.d ${OBJECTDIR}/_ext/246898221/drv_usbhs.o.d ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o.d ${OBJECTDIR}/_ext/30809027/sys_console.o.d ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o.d ${OBJECTDIR}/_ext/1408546951/sys_debug.o.d ${OBJECTDIR}/_ext/2104899551/sys_fs.o.d ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o.d ${OBJECTDIR}/_ext/66287330/ff.o.d ${OBJECTDIR}/_ext/2072869785/diskio.o.d ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d ${OBJECTDIR}/_ext/1283840359/sys_random.o.d ${OBJECTDIR}/_ext/1264926591/sys_tmr.o.d ${OBJECTDIR}/_ext/610166344/usb_device.o.d ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o.d ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1390850504/FT8_commands.o ${OBJECTDIR}/_ext/1019118654/expression.o ${OBJECTDIR}/_ext/1019118654/expr_tokens.o ${OBJECTDIR}/_ext/1019118654/list64.o ${OBJECTDIR}/_ext/1019118654/tuplestack.o ${OBJECTDIR}/_ext/1019118654/vars.o ${OBJECTDIR}/_ext/1019118654/mathext.o ${OBJECTDIR}/_ext/705376131/keyboard.o ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o ${OBJECTDIR}/_ext/715571337/drv_spi_static.o ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ${OBJECTDIR}/_ext/476726740/sys_rtcc.o ${OBJECTDIR}/_ext/1688732426/system_init.o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/280795049/drv_i2c.o ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o ${OBJECTDIR}/_ext/1868400972/drv_sram.o ${OBJECTDIR}/_ext/185269848/drv_tmr.o ${OBJECTDIR}/_ext/246898221/drv_usbhs.o ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o ${OBJECTDIR}/_ext/30809027/sys_console.o ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o ${OBJECTDIR}/_ext/1408546951/sys_debug.o ${OBJECTDIR}/_ext/2104899551/sys_fs.o ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o ${OBJECTDIR}/_ext/66287330/ff.o ${OBJECTDIR}/_ext/2072869785/diskio.o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ${OBJECTDIR}/_ext/1283840359/sys_random.o ${OBJECTDIR}/_ext/1264926591/sys_tmr.o ${OBJECTDIR}/_ext/610166344/usb_device.o ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o

# Source Files
SOURCEFILES=../src/display/FT8_commands.c ../src/math/expression.c ../src/math/expr_tokens.c ../src/math/list64.c ../src/math/tuplestack.c ../src/math/vars.c ../src/math/mathext.c ../src/peripherals/keyboard.c ../src/system_config/default/framework/driver/adc/src/drv_adc_static.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S ../src/system_config/default/framework/system/memory/ebi/src/sys_memory_ebi_static.c ../src/system_config/default/framework/system/memory/src/sys_memory_static.c ../src/system_config/default/framework/system/ports/src/sys_ports_static.c ../src/system_config/default/framework/system/rtcc/sys_rtcc.c ../src/system_config/default/system_init.c ../src/system_config/default/system_interrupt.c ../src/system_config/default/system_exceptions.c ../src/system_config/default/system_tasks.c ../src/app.c ../src/main.c ../../../../framework/driver/i2c/src/dynamic/drv_i2c.c ../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c ../src/framework/driver/sram/src/dynamic/drv_sram.c ../../../../framework/driver/tmr/src/dynamic/drv_tmr.c ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c ../../../../framework/system/console/src/sys_console.c ../../../../framework/system/console/src/sys_console_usb_cdc.c ../../../../framework/system/debug/src/sys_debug.c ../../../../framework/system/fs/src/dynamic/sys_fs.c ../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c ../../../../framework/system/fs/fat_fs/src/file_system/ff.c ../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c ../../../../framework/system/int/src/sys_int_pic32.c ../../../../framework/system/random/src/sys_random.c ../../../../framework/system/tmr/src/sys_tmr.c ../../../../framework/usb/src/dynamic/usb_device.c ../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFH144
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  .generated_files/flags/default/27f69de772b3ae3ce955c0cedb06036ca13659c3 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  .generated_files/flags/default/8bacf5f2af3976502df36b9c8bc90390412b25fc .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d",--gdwarf-2 
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1390850504/FT8_commands.o: ../src/display/FT8_commands.c  .generated_files/flags/default/2782772ac2eb1ac3ffdbcf368309f6ad6d17bdcd .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1390850504" 
	@${RM} ${OBJECTDIR}/_ext/1390850504/FT8_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390850504/FT8_commands.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1390850504/FT8_commands.o.d" -o ${OBJECTDIR}/_ext/1390850504/FT8_commands.o ../src/display/FT8_commands.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/expression.o: ../src/math/expression.c  .generated_files/flags/default/6a6134cfd9aec2daca896ac10b9d93ef260ccc6a .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expression.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expression.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/expression.o.d" -o ${OBJECTDIR}/_ext/1019118654/expression.o ../src/math/expression.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/expr_tokens.o: ../src/math/expr_tokens.c  .generated_files/flags/default/47509a42e5bf4d82ab6b2838229fae5b2f8f85d4 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expr_tokens.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expr_tokens.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/expr_tokens.o.d" -o ${OBJECTDIR}/_ext/1019118654/expr_tokens.o ../src/math/expr_tokens.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/list64.o: ../src/math/list64.c  .generated_files/flags/default/4681a5738019dcee7602b11708faa8ea65f09fc7 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/list64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/list64.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/list64.o.d" -o ${OBJECTDIR}/_ext/1019118654/list64.o ../src/math/list64.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/tuplestack.o: ../src/math/tuplestack.c  .generated_files/flags/default/d6ea5996b3feff1e71954e2dbbf18aae5f396472 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/tuplestack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/tuplestack.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/tuplestack.o.d" -o ${OBJECTDIR}/_ext/1019118654/tuplestack.o ../src/math/tuplestack.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/vars.o: ../src/math/vars.c  .generated_files/flags/default/b553738443dc12d052dfebc22495e8a7740f780b .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/vars.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/vars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/vars.o.d" -o ${OBJECTDIR}/_ext/1019118654/vars.o ../src/math/vars.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/mathext.o: ../src/math/mathext.c  .generated_files/flags/default/9dad1ebebfedd32a89490e27642aaa43778a5cc7 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/mathext.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/mathext.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/mathext.o.d" -o ${OBJECTDIR}/_ext/1019118654/mathext.o ../src/math/mathext.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/705376131/keyboard.o: ../src/peripherals/keyboard.c  .generated_files/flags/default/f0374ec4db32af7e5dbd9a0038ab8a6567f5a62c .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/705376131" 
	@${RM} ${OBJECTDIR}/_ext/705376131/keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/705376131/keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/705376131/keyboard.o.d" -o ${OBJECTDIR}/_ext/705376131/keyboard.o ../src/peripherals/keyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1361460060/drv_adc_static.o: ../src/system_config/default/framework/driver/adc/src/drv_adc_static.c  .generated_files/flags/default/1ef12d5084e7f9073d36516012ce9411e6ab48fd .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1361460060" 
	@${RM} ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1361460060/drv_adc_static.o.d" -o ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o ../src/system_config/default/framework/driver/adc/src/drv_adc_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c  .generated_files/flags/default/4d72235d9d188010defb821a7dcb44aeb21a70f4 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c  .generated_files/flags/default/2f88c1b525a8904900900d109f5ada822ea5dfd6 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c  .generated_files/flags/default/e031d9afe290f5953e4b3b3602acfccfada3f322 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c  .generated_files/flags/default/a6bc89256f1c6a3f8c36d9e4cc53c4354f018fb7 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c  .generated_files/flags/default/fe051253d4c85a4d0461227315fc52f269b83b4d .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o: ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c  .generated_files/flags/default/956fee8d6b8dd411a6ba25fd5eb852923e06fd43 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/639803181" 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d" -o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/340578644/sys_devcon.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/default/937b884246bfbc7fe5d8566e3306d9f7cf02e93b .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ../src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c  .generated_files/flags/default/f8d03730d607358f6ff9adc120eca6788ebd1bd2 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o: ../src/system_config/default/framework/system/memory/ebi/src/sys_memory_ebi_static.c  .generated_files/flags/default/932232e3cde423edd3d1424b09f4e716beceed8b .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1316854077" 
	@${RM} ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o.d" -o ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o ../src/system_config/default/framework/system/memory/ebi/src/sys_memory_ebi_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1541531744/sys_memory_static.o: ../src/system_config/default/framework/system/memory/src/sys_memory_static.c  .generated_files/flags/default/63ab366354c8f6c063cd78ced48801ede082e86a .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1541531744" 
	@${RM} ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1541531744/sys_memory_static.o.d" -o ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o ../src/system_config/default/framework/system/memory/src/sys_memory_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/822048611/sys_ports_static.o: ../src/system_config/default/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/default/84a85e6074b5407a4c293e4ca96f47a3a0312e51 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/822048611" 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ../src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/476726740/sys_rtcc.o: ../src/system_config/default/framework/system/rtcc/sys_rtcc.c  .generated_files/flags/default/3d16e8dbe045c37120814914b084970a2e1c3980 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/476726740" 
	@${RM} ${OBJECTDIR}/_ext/476726740/sys_rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/476726740/sys_rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/476726740/sys_rtcc.o.d" -o ${OBJECTDIR}/_ext/476726740/sys_rtcc.o ../src/system_config/default/framework/system/rtcc/sys_rtcc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_init.o: ../src/system_config/default/system_init.c  .generated_files/flags/default/65d5c8a6c430a5b7bdc3cd00f5d5bcb6b474054a .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_init.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_init.o ../src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_interrupt.o: ../src/system_config/default/system_interrupt.c  .generated_files/flags/default/9e2f117ac5d1553fa512a40459aa1a9527d305fb .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ../src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_exceptions.o: ../src/system_config/default/system_exceptions.c  .generated_files/flags/default/8d24558fd2a328dd793cbac1c4ae4b37674d4ad2 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ../src/system_config/default/system_exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_tasks.o: ../src/system_config/default/system_tasks.c  .generated_files/flags/default/25007fee986706cc1019491ef9ca45091772466c .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ../src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/9505f6931c7faf3301c1c5953eca77342f019941 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/c1c1a4cca25e38e521a2edc6760e8adfc71cf8ff .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/280795049/drv_i2c.o: ../../../../framework/driver/i2c/src/dynamic/drv_i2c.c  .generated_files/flags/default/da89a03fbc41cead7eec58daca18b69821cac313 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/280795049" 
	@${RM} ${OBJECTDIR}/_ext/280795049/drv_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/280795049/drv_i2c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/280795049/drv_i2c.o.d" -o ${OBJECTDIR}/_ext/280795049/drv_i2c.o ../../../../framework/driver/i2c/src/dynamic/drv_i2c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2000565276/drv_sdcard.o: ../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c  .generated_files/flags/default/e8b66236ed0dda7b984ef6c1eaa55394e7ef91c9 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2000565276" 
	@${RM} ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o.d 
	@${RM} ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2000565276/drv_sdcard.o.d" -o ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o ../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1868400972/drv_sram.o: ../src/framework/driver/sram/src/dynamic/drv_sram.c  .generated_files/flags/default/12bd0fcca741f20a3a3476cbb1515d16bd27d788 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1868400972" 
	@${RM} ${OBJECTDIR}/_ext/1868400972/drv_sram.o.d 
	@${RM} ${OBJECTDIR}/_ext/1868400972/drv_sram.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1868400972/drv_sram.o.d" -o ${OBJECTDIR}/_ext/1868400972/drv_sram.o ../src/framework/driver/sram/src/dynamic/drv_sram.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/185269848/drv_tmr.o: ../../../../framework/driver/tmr/src/dynamic/drv_tmr.c  .generated_files/flags/default/82deca9635a982bb3d313787102dde832e10602f .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/185269848" 
	@${RM} ${OBJECTDIR}/_ext/185269848/drv_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/185269848/drv_tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/185269848/drv_tmr.o.d" -o ${OBJECTDIR}/_ext/185269848/drv_tmr.o ../../../../framework/driver/tmr/src/dynamic/drv_tmr.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/246898221/drv_usbhs.o: ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c  .generated_files/flags/default/ce81e29081e15a1f7a019ec2f7516effe7245961 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/246898221" 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/246898221/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/246898221/drv_usbhs.o ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o: ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c  .generated_files/flags/default/1d386a15689beaadaac9343ffede6e7fcb4b9f89 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/246898221" 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/30809027/sys_console.o: ../../../../framework/system/console/src/sys_console.c  .generated_files/flags/default/b84ebef89aaf964488364218c76c90df6501e677 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/30809027" 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/30809027/sys_console.o.d" -o ${OBJECTDIR}/_ext/30809027/sys_console.o ../../../../framework/system/console/src/sys_console.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o: ../../../../framework/system/console/src/sys_console_usb_cdc.c  .generated_files/flags/default/b0a832dd3ce3acfb72a50c2d45afe5f03ddba72 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/30809027" 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o.d" -o ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o ../../../../framework/system/console/src/sys_console_usb_cdc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1408546951/sys_debug.o: ../../../../framework/system/debug/src/sys_debug.c  .generated_files/flags/default/a3a80ef03b2e8a4c174665a3630f62f73b1b5afa .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1408546951" 
	@${RM} ${OBJECTDIR}/_ext/1408546951/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1408546951/sys_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1408546951/sys_debug.o.d" -o ${OBJECTDIR}/_ext/1408546951/sys_debug.o ../../../../framework/system/debug/src/sys_debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2104899551/sys_fs.o: ../../../../framework/system/fs/src/dynamic/sys_fs.c  .generated_files/flags/default/b9c68d659cde57d46aec45291d4a63f7b0573bf4 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2104899551" 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2104899551/sys_fs.o.d" -o ${OBJECTDIR}/_ext/2104899551/sys_fs.o ../../../../framework/system/fs/src/dynamic/sys_fs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o: ../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c  .generated_files/flags/default/e687e2f6e7a0b033ecba2e0c7a606d5cd97f61a6 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2104899551" 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o ../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/66287330/ff.o: ../../../../framework/system/fs/fat_fs/src/file_system/ff.c  .generated_files/flags/default/a2b15075944989e3efe31bb292d392a5c6235a18 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/66287330" 
	@${RM} ${OBJECTDIR}/_ext/66287330/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/66287330/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/66287330/ff.o.d" -o ${OBJECTDIR}/_ext/66287330/ff.o ../../../../framework/system/fs/fat_fs/src/file_system/ff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2072869785/diskio.o: ../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c  .generated_files/flags/default/f1f721918f38cfd47988dd1be66cf09a0edca57f .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2072869785" 
	@${RM} ${OBJECTDIR}/_ext/2072869785/diskio.o.d 
	@${RM} ${OBJECTDIR}/_ext/2072869785/diskio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2072869785/diskio.o.d" -o ${OBJECTDIR}/_ext/2072869785/diskio.o ../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/122796885/sys_int_pic32.o: ../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/default/9bcba572861832dac5b58cfcf2e5675ae78fc4bc .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/122796885" 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1283840359/sys_random.o: ../../../../framework/system/random/src/sys_random.c  .generated_files/flags/default/84a16636a78d1442e777d9bbdcb4e3c916ec193 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1283840359" 
	@${RM} ${OBJECTDIR}/_ext/1283840359/sys_random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1283840359/sys_random.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1283840359/sys_random.o.d" -o ${OBJECTDIR}/_ext/1283840359/sys_random.o ../../../../framework/system/random/src/sys_random.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1264926591/sys_tmr.o: ../../../../framework/system/tmr/src/sys_tmr.c  .generated_files/flags/default/28bd58aea2d4f6621f784f33c96ecc55d60285e5 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1264926591" 
	@${RM} ${OBJECTDIR}/_ext/1264926591/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1264926591/sys_tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1264926591/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/1264926591/sys_tmr.o ../../../../framework/system/tmr/src/sys_tmr.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/610166344/usb_device.o: ../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/default/c62bcd726254d491276ae1c325795698aeff452a .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/610166344" 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/610166344/usb_device.o.d" -o ${OBJECTDIR}/_ext/610166344/usb_device.o ../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/610166344/usb_device_cdc.o: ../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/default/fd266828036142d1b508282c3bc8dce924b8982d .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/610166344" 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/610166344/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o ../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o: ../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/default/366e81c81c50b858718e7c428115530295ee8071 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/610166344" 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o ../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
else
${OBJECTDIR}/_ext/1390850504/FT8_commands.o: ../src/display/FT8_commands.c  .generated_files/flags/default/b4156722a29378cde86e28361dc7af2634171917 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1390850504" 
	@${RM} ${OBJECTDIR}/_ext/1390850504/FT8_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390850504/FT8_commands.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1390850504/FT8_commands.o.d" -o ${OBJECTDIR}/_ext/1390850504/FT8_commands.o ../src/display/FT8_commands.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/expression.o: ../src/math/expression.c  .generated_files/flags/default/893f4a83ebe4ded2590837fb37832be326f573d4 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expression.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expression.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/expression.o.d" -o ${OBJECTDIR}/_ext/1019118654/expression.o ../src/math/expression.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/expr_tokens.o: ../src/math/expr_tokens.c  .generated_files/flags/default/4e5fd69692f6ac6678a3704e85f964dc0ea6a086 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expr_tokens.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/expr_tokens.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/expr_tokens.o.d" -o ${OBJECTDIR}/_ext/1019118654/expr_tokens.o ../src/math/expr_tokens.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/list64.o: ../src/math/list64.c  .generated_files/flags/default/504e62a7c171b6e72eb9964eb59a88424a70ba9c .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/list64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/list64.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/list64.o.d" -o ${OBJECTDIR}/_ext/1019118654/list64.o ../src/math/list64.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/tuplestack.o: ../src/math/tuplestack.c  .generated_files/flags/default/d8d2539a93a6861f8aee6e499b597a8f4dc74c37 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/tuplestack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/tuplestack.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/tuplestack.o.d" -o ${OBJECTDIR}/_ext/1019118654/tuplestack.o ../src/math/tuplestack.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/vars.o: ../src/math/vars.c  .generated_files/flags/default/41eb4eeed60c8860d184b1cdde9478fb7107d227 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/vars.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/vars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/vars.o.d" -o ${OBJECTDIR}/_ext/1019118654/vars.o ../src/math/vars.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1019118654/mathext.o: ../src/math/mathext.c  .generated_files/flags/default/6af144f12ef110bdfe8d7c1c24be2b62c02a26c7 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1019118654" 
	@${RM} ${OBJECTDIR}/_ext/1019118654/mathext.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019118654/mathext.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1019118654/mathext.o.d" -o ${OBJECTDIR}/_ext/1019118654/mathext.o ../src/math/mathext.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/705376131/keyboard.o: ../src/peripherals/keyboard.c  .generated_files/flags/default/a89a06c49b667f7b553c178a9516a474f168c608 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/705376131" 
	@${RM} ${OBJECTDIR}/_ext/705376131/keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/705376131/keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/705376131/keyboard.o.d" -o ${OBJECTDIR}/_ext/705376131/keyboard.o ../src/peripherals/keyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1361460060/drv_adc_static.o: ../src/system_config/default/framework/driver/adc/src/drv_adc_static.c  .generated_files/flags/default/ba8db08a4c6006e69e009bc74cda8f3836215087 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1361460060" 
	@${RM} ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1361460060/drv_adc_static.o.d" -o ${OBJECTDIR}/_ext/1361460060/drv_adc_static.o ../src/system_config/default/framework/driver/adc/src/drv_adc_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c  .generated_files/flags/default/7538828e31cbaabfe767367ebeaa2b543f7443d .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c  .generated_files/flags/default/76d4506be24aa7dc55354d5b24b12ae2ee310943 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_mapping.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c  .generated_files/flags/default/869ce5eed94fe7fe60ad155bb87fb7dcf4978021 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static_tasks.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c  .generated_files/flags/default/5df5726ecf16bd10b1b15fde22803c539a1c0864 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static_sys_queue.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o: ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c  .generated_files/flags/default/25684e09d595dc0a1a95e441c8980cac3e5c4435 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/715571337" 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o.d" -o ${OBJECTDIR}/_ext/715571337/drv_spi_static_ebm_tasks.o ../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o: ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c  .generated_files/flags/default/e4162bea601c63c8f2bd322d10c94288c262104c .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/639803181" 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d" -o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/340578644/sys_devcon.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/default/4096106336daa6b20bfc854c38791d8acc0e906 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ../src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c  .generated_files/flags/default/486d32ee05990769ad0e787bd40b55eb338d8ba2 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o: ../src/system_config/default/framework/system/memory/ebi/src/sys_memory_ebi_static.c  .generated_files/flags/default/a60ee4eeeafa73d52103419a6784c04e71c377c0 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1316854077" 
	@${RM} ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o.d" -o ${OBJECTDIR}/_ext/1316854077/sys_memory_ebi_static.o ../src/system_config/default/framework/system/memory/ebi/src/sys_memory_ebi_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1541531744/sys_memory_static.o: ../src/system_config/default/framework/system/memory/src/sys_memory_static.c  .generated_files/flags/default/4e9c778c33cbc6d8526a9c3711ae0ae920cb7bdf .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1541531744" 
	@${RM} ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1541531744/sys_memory_static.o.d" -o ${OBJECTDIR}/_ext/1541531744/sys_memory_static.o ../src/system_config/default/framework/system/memory/src/sys_memory_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/822048611/sys_ports_static.o: ../src/system_config/default/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/default/498a916c2a688f8a90d4c8c1c2f5e69e42c244ad .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/822048611" 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ../src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/476726740/sys_rtcc.o: ../src/system_config/default/framework/system/rtcc/sys_rtcc.c  .generated_files/flags/default/bfc6d7851bdce903b69fa2e8fece3e75d218952a .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/476726740" 
	@${RM} ${OBJECTDIR}/_ext/476726740/sys_rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/476726740/sys_rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/476726740/sys_rtcc.o.d" -o ${OBJECTDIR}/_ext/476726740/sys_rtcc.o ../src/system_config/default/framework/system/rtcc/sys_rtcc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_init.o: ../src/system_config/default/system_init.c  .generated_files/flags/default/96d95e7a47777c620deb0a49f9eb1f5ca0a5b775 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_init.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_init.o ../src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_interrupt.o: ../src/system_config/default/system_interrupt.c  .generated_files/flags/default/cb869c682620d23008486dd8470535848295de4d .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ../src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_exceptions.o: ../src/system_config/default/system_exceptions.c  .generated_files/flags/default/4681c997f4593c85646e03b5536e8c52a74b6daf .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ../src/system_config/default/system_exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1688732426/system_tasks.o: ../src/system_config/default/system_tasks.c  .generated_files/flags/default/11ecc09907235be4595df9c006f0e147feb98be8 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ../src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/1acf2fb1b59e05de74a8f6dd10a59d65d4be430f .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/f13830b18513fb5935da6275aad59f41355cd9fa .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/280795049/drv_i2c.o: ../../../../framework/driver/i2c/src/dynamic/drv_i2c.c  .generated_files/flags/default/cf3dd36bdc69077b6848da94e81059c0a5dda04d .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/280795049" 
	@${RM} ${OBJECTDIR}/_ext/280795049/drv_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/280795049/drv_i2c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/280795049/drv_i2c.o.d" -o ${OBJECTDIR}/_ext/280795049/drv_i2c.o ../../../../framework/driver/i2c/src/dynamic/drv_i2c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2000565276/drv_sdcard.o: ../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c  .generated_files/flags/default/4f1965afab7fdaf57f7ae10872e87bed98275348 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2000565276" 
	@${RM} ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o.d 
	@${RM} ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2000565276/drv_sdcard.o.d" -o ${OBJECTDIR}/_ext/2000565276/drv_sdcard.o ../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1868400972/drv_sram.o: ../src/framework/driver/sram/src/dynamic/drv_sram.c  .generated_files/flags/default/8ed04afe58288ebb823ce167220591557d519997 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1868400972" 
	@${RM} ${OBJECTDIR}/_ext/1868400972/drv_sram.o.d 
	@${RM} ${OBJECTDIR}/_ext/1868400972/drv_sram.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1868400972/drv_sram.o.d" -o ${OBJECTDIR}/_ext/1868400972/drv_sram.o ../src/framework/driver/sram/src/dynamic/drv_sram.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/185269848/drv_tmr.o: ../../../../framework/driver/tmr/src/dynamic/drv_tmr.c  .generated_files/flags/default/fcf043b0f536a676091d2ad89028b7517f61f08f .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/185269848" 
	@${RM} ${OBJECTDIR}/_ext/185269848/drv_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/185269848/drv_tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/185269848/drv_tmr.o.d" -o ${OBJECTDIR}/_ext/185269848/drv_tmr.o ../../../../framework/driver/tmr/src/dynamic/drv_tmr.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/246898221/drv_usbhs.o: ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c  .generated_files/flags/default/287f3f0b6dc59d8b0e9847444b3e458a783c125e .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/246898221" 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/246898221/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/246898221/drv_usbhs.o ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o: ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c  .generated_files/flags/default/8b4aeec74664a3bfe2b8865ac5b9a4809eec32f1 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/246898221" 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/246898221/drv_usbhs_device.o ../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/30809027/sys_console.o: ../../../../framework/system/console/src/sys_console.c  .generated_files/flags/default/9dfac21acd133d6e88ead45cfd1eeccde07630f7 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/30809027" 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/30809027/sys_console.o.d" -o ${OBJECTDIR}/_ext/30809027/sys_console.o ../../../../framework/system/console/src/sys_console.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o: ../../../../framework/system/console/src/sys_console_usb_cdc.c  .generated_files/flags/default/eb33ff6b3f61c4e7ebbd2a977ef0bfe0203021c0 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/30809027" 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o.d" -o ${OBJECTDIR}/_ext/30809027/sys_console_usb_cdc.o ../../../../framework/system/console/src/sys_console_usb_cdc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1408546951/sys_debug.o: ../../../../framework/system/debug/src/sys_debug.c  .generated_files/flags/default/9b4553803eb746fccacbcef123fd11aef5fb8e7f .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1408546951" 
	@${RM} ${OBJECTDIR}/_ext/1408546951/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1408546951/sys_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1408546951/sys_debug.o.d" -o ${OBJECTDIR}/_ext/1408546951/sys_debug.o ../../../../framework/system/debug/src/sys_debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2104899551/sys_fs.o: ../../../../framework/system/fs/src/dynamic/sys_fs.c  .generated_files/flags/default/53676a885bffb2e0e3b9f7b35465904f43f55266 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2104899551" 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2104899551/sys_fs.o.d" -o ${OBJECTDIR}/_ext/2104899551/sys_fs.o ../../../../framework/system/fs/src/dynamic/sys_fs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o: ../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c  .generated_files/flags/default/29e423444629322398df20adf7850eb76530e204 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2104899551" 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/2104899551/sys_fs_media_manager.o ../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/66287330/ff.o: ../../../../framework/system/fs/fat_fs/src/file_system/ff.c  .generated_files/flags/default/e1546e0407c2f32d9998027d76a04b3d12bf9089 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/66287330" 
	@${RM} ${OBJECTDIR}/_ext/66287330/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/66287330/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/66287330/ff.o.d" -o ${OBJECTDIR}/_ext/66287330/ff.o ../../../../framework/system/fs/fat_fs/src/file_system/ff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/2072869785/diskio.o: ../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c  .generated_files/flags/default/81e8ca5add74b237aef9d0b368f3dd14ffda0989 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/2072869785" 
	@${RM} ${OBJECTDIR}/_ext/2072869785/diskio.o.d 
	@${RM} ${OBJECTDIR}/_ext/2072869785/diskio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2072869785/diskio.o.d" -o ${OBJECTDIR}/_ext/2072869785/diskio.o ../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/122796885/sys_int_pic32.o: ../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/default/3dcb5ddb972ea5f7ccfbfe85eefdb5bd7b9dc069 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/122796885" 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1283840359/sys_random.o: ../../../../framework/system/random/src/sys_random.c  .generated_files/flags/default/a3517ddec45896186b9c8d7fb00bd62aa6239795 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1283840359" 
	@${RM} ${OBJECTDIR}/_ext/1283840359/sys_random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1283840359/sys_random.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1283840359/sys_random.o.d" -o ${OBJECTDIR}/_ext/1283840359/sys_random.o ../../../../framework/system/random/src/sys_random.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/1264926591/sys_tmr.o: ../../../../framework/system/tmr/src/sys_tmr.c  .generated_files/flags/default/efddb98ed9e028e98a4845a84e6cf8bf9e0e41af .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/1264926591" 
	@${RM} ${OBJECTDIR}/_ext/1264926591/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1264926591/sys_tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1264926591/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/1264926591/sys_tmr.o ../../../../framework/system/tmr/src/sys_tmr.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/610166344/usb_device.o: ../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/default/fa8d7c00ad7e794377115f1628be8b576733716 .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/610166344" 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/610166344/usb_device.o.d" -o ${OBJECTDIR}/_ext/610166344/usb_device.o ../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/610166344/usb_device_cdc.o: ../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/default/1f5493c2b09eb702c36ba7893f6202bf11a0463c .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/610166344" 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/610166344/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/610166344/usb_device_cdc.o ../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o: ../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/default/a6df08744596e20bd5c99584f3cdc8869f6ba64d .generated_files/flags/default/43be9d5028dca0d5960a148faf0b2b5e7e3013c
	@${MKDIR} "${OBJECTDIR}/_ext/610166344" 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/610166344/usb_device_cdc_acm.o ../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fno-short-double   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../bin/framework/peripheral/PIC32MZ2048EFH144_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\bin\framework\peripheral\PIC32MZ2048EFH144_peripherals.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=32786,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../bin/framework/peripheral/PIC32MZ2048EFH144_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\bin\framework\peripheral\PIC32MZ2048EFH144_peripherals.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=32786,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DigitalMultitool.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

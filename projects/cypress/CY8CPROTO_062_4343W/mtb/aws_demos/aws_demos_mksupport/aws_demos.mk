#################################################################################
## \file smac_demos.mk
## \version 1.0
##
## \brief
## Configuration file setting up the required Applicalibraries, dependencies for
## smac_demo based on the smart sensor firmware
##
#################################################################################
#
#################################################################################
## demo sources
## Todo: the demo files will be replaced 
#################################################################################
#
## Demo Application source file
#SOURCES+=$(CY_AFR_ROOT)/demos/smac_demo_app/application/smac_demo_mqtt.c
#
## Demo support source files
#SOURCES+=\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/src/iot_smart_sensor_dps310.c\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/src/pasco2_demo.c\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/src/imotion2go.c\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/src/timestamp.c\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/src/bsp_board.c\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/src/csk_radar_wingboard.c
##	$(CY_AFR_ROOT)/demos/smac_demo_app/application/smac_app.c
##	$(CY_AFR_ROOT)/demos/smac_demo_app/src/bsp_board.c\
##	$(CY_AFR_ROOT)/demos/smac_demo_app/src/bsp_capsense.c\
##	$(CY_AFR_ROOT)/demos/smac_demo_app/src/timestamp.c\
##	$(CY_AFR_ROOT)/demos/smac_demo_app/src/csk_pasco2_wingboard.c\
##	$(CY_AFR_ROOT)/demos/smac_demo_app/src/csk_radar_wingboard.c\
#
## Demo support header files
#INCLUDES+=\
#	$(CY_AFR_ROOT)/demos/smac_demo_app/includes
#
#################################################################################
## libraries (sensor/actuator libraries)
#################################################################################
# Radar library sources
# Library Directory name
LIB_NAME=radar-bgt60-develop_c@96d1f697f50
# Corelib
SOURCES+=\
	$(wildcard $(CY_AFR_ROOT)/libraries/${LIB_NAME}/src/corelib/*.c)

INCLUDES+=\
	$(CY_AFR_ROOT)/libraries/${LIB_NAME}/src/corelib

# Framework
SOURCES+=\
	$(wildcard $(CY_AFR_ROOT)/libraries/${LIB_NAME}/src/framework/psoc6/pal/*.c)\
	$(wildcard $(CY_AFR_ROOT)/libraries/${LIB_NAME}/src/framework/psoc6/wrapper/*.c)

INCLUDES+=\
	$(CY_AFR_ROOT)/libraries/${LIB_NAME}/src/framework/psoc6/pal\
	$(CY_AFR_ROOT)/libraries/${LIB_NAME}/src/framework/psoc6/wrapper


#
## DPS310 Library
#SOURCES+=\
#	$(wildcard $(CY_AFR_ROOT)/libraries/dps310_pressure_sensor/*.c)
#
#INCLUDES+=\
#	$(CY_AFR_ROOT)/libraries/dps310_pressure_sensor
#
## Xensiv PAS CO2 Library - Pre-compiled Library
## This sensor libraries are provided as pre-compiled libaries. 
## They are added to the MiddleWare folder under vendors
#
## Xensiv RADAR Library - Pre-compiled Library
## This sensor libraries are provided as pre-compiled libaries. 
## They are added to the MiddleWare folder under vendors
#
## RGB LED library (version - 1.2.0.21063)
#SOURCES+=\
#	$(wildcard $(CY_AFR_ROOT)/libraries/rgb-led/*.c)
#
#INCLUDES+=\
#	$(CY_AFR_ROOT)/libraries/rgb-led
#

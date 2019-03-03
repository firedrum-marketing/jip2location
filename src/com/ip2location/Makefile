#
# Source level Makefile for JIP2Location.
#
# NOTE: Define DESTDIR if you are not installing JIP2Location
#       to its final directories. This is meant for the
#       purpose of packaging.
#
MAKE_PATH = ../../..
include $(MAKE_PATH)/Make.def

# JNI specifications
JNI_LIB_NAME    =	JIP2Location
JNI_SRC_FILES   =	IP2Location.java

JNI_LINK_LIBS   =	$(IP2LOCATION_LIBS)

INCLUDES        =	$(JAVA_INCLUDES) $(IP2LOCATION_INCLUDES)

CLEAN_LIST	=	$(JNI_LIB) $(LIB_DIR)/.libs

include $(MAKE_PATH)/Make.rules

extra-install::
	$(INSTALL) -d $(DESTDIR)$(libdir)
	$(LIBTOOL) --mode=install $(INSTALL) $(JNI_LIB) $(DESTDIR)$(libdir)

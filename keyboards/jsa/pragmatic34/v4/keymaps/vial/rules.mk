VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes
QMK_SETTINGS = yes

EXTRAFLAGS += -flto

CUSTOM_MATRIX = lite
SRC += matrix.c

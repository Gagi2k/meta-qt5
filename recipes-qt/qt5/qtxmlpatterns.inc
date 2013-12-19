require qt5.inc

DEPENDS += "qtbase"

ALTERNATIVE_qtxmlpatterns-tools = "xmlpatterns xmlpatternsvalidator"
ALTERNATIVE_TARGET[xmlpatterns] = "${OE_QMAKE_PATH_BINS}/xmlpatterns"
ALTERNATIVE_TARGET[xmlpatternsvalidator] = "${OE_QMAKE_PATH_BINS}/xmlpatternsvalidator"

# SPDX-FileCopyrightText: 2018 Philippe Proulx <eepp.ca>
# SPDX-License-Identifier: MIT

if (YACTFR_INSTALL)
    install (
        DIRECTORY yactfr
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endif ()

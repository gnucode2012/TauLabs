/**
 ******************************************************************************
 * @file       waypointeditorgadget.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup Waypoint Editor GCS Plugins
 * @{
 * @addtogroup WaypointEditorGadgetPlugin Waypoint Editor Gadget Plugin
 * @{
 * @brief A gadget to edit a list of waypoints
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include "waypointeditorgadget.h"
#include "waypointeditorgadgetwidget.h"

#include "extensionsystem/pluginmanager.h"
#include "uavobjectmanager.h"
#include "uavobject.h"
#include <QDebug>

WaypointEditorGadget::WaypointEditorGadget(QString classId, WaypointEditorGadgetWidget *widget, QWidget *parent) :
        IUAVGadget(classId, parent),
        m_widget(widget)
{
}

WaypointEditorGadget::~WaypointEditorGadget()
{
    delete m_widget;
}

void WaypointEditorGadget::loadConfiguration(IUAVGadgetConfiguration* config)
{
    Q_UNUSED(config);
}

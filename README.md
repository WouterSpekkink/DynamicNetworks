DynamicNetworks
===============
This file is part of Dynamic Networks

Dynamic Networks is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
ihe Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Dynamic Networks is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

================

Dynamic Networks is intended as a tool to be used alongside Gephi (https://gephi.github.io/)
The tool works with incidence matrices that are saved as a .csv file.
The tool is only useful if the columns of the matrix represent events that are put in temporal order.
An example is offered below.

                Event1    Event2    Event3    Event4
        ActorA    1         0         1         0
        ActorB    0         1         0         1
        ActorC    1         1         0         0

The tool can be used to convert the incidence matrix into various types of edge lists that can
be imported into Gephi.

================
The graphical interface was made with the open source version of the Qt library. You'll need Qt 4.8 to build this program.

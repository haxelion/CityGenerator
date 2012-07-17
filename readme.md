CityGenerator
=============

1. Introduction
----------------

This software generate a city using a simple recursive algorithm and display it in 3D in a nice GUI. This software is _totally useless.
Copyright (C) 2012  Charles 'haxelion' Hubain

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

2. Some technical details
-------------------------

This software was created for my programmation course. It use Qt 4.7 and Opengl 3.X. It was entirely programmed and compiled on windows, but it should run on linux (maybe with some minor changes). It also use GLM for matrix computations and glew for OpenGL loading.


The city generation algorithm is a quite simple recursive algorithm and was imposed. It does not generate realistic city at all.
The OpenGL code make use of VAO, VBO, IBO and shaders. The shaders are not very complex but make a nice reflection effect.

Oh yeah, and the sun is rotating around the scene ^^

3. Warning
----------

This code was written very fastly during a busy semester. It is _awful_ and _badly_ structured. It need a lot of refactoring but there was no time for it.
Also the commit messages are in french.

4. License
----------


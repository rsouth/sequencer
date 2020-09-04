/*
 *     Copyright (C) 2020 rsouth (https://github.com/rsouth)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <string>

#include "RenderingUtils.h"

class MetaData
{
public:
  MetaData();
  MetaData(std::string title, std::string author, std::string date, RenderingUtils::Theme theme = RenderingUtils::Theme::Default);

  auto get_title() const->std::string;
  auto get_author() const->std::string;
  auto get_date() const->std::string;
  auto get_theme() const->RenderingUtils::Theme;

private:
  std::string title_ = std::string();
  std::string author_ = std::string();
  std::string date_ = std::string();
  RenderingUtils::Theme theme_ = RenderingUtils::Theme::Default;
};

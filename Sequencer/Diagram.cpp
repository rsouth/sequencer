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
#include "Diagram.h"

#include <utility>

Diagram::Diagram(const MetaData& meta_data, std::list<Participant> participants, std::list<Interaction> interactions):
	meta_data_(meta_data),
	participants_(std::move(participants)),
	interactions_(std::move(interactions))
{
}

MetaData Diagram::get_meta_data() const
{
	return this->meta_data_;
}

std::list<Participant> Diagram::get_participants() const
{
	return this->participants_;
}

std::list<Interaction> Diagram::get_interactions() const
{
	return this->interactions_;
}

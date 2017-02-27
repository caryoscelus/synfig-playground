/* === S Y N F I G ========================================================= */
/*!	\file skeleton.cpp
**	\brief Automatic skeleton influence value node
**
**	\legal
**	Copyright (c) 2017 caryoscelus
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/

#include "skeleton.h"

#include <synfig/valuenode_registry.h>
#include <synfig/general.h>
#include <synfig/blinepoint.h>
#include <synfig/bone.h>
#include <synfig/valueoperations.h>
#include <synfig/weightedvalue.h>
#include <synfig/valuenodes/valuenode_const.h>
#include <synfig/valuenodes/valuenode_staticlist.h>
#include <synfig/valuenodes/valuenode_weightedaverage.h>
#include <synfig/valuenodes/valuenode_bone.h>
#include <synfig/valuenodes/valuenode_bonelink.h>

#include <algorithm>

using namespace synfig::valuenodes;
REGISTER_VALUENODE(SkeletonInfluence, RELEASE_VERSION_CURRENT, "skeleton_influence", "Skeleton Influence")

namespace synfig {
namespace valuenodes {

SkeletonInfluence::SkeletonInfluence(const ValueBase& value) :
	LinkableValueNode(value.get_type())
{
	path_ = ValueNode_Const::create(value);
	skeleton_ = ValueNode_Const::create(ValueBase(std::vector<ValueNode_Bone::Handle>()));
}

ValueBase
SkeletonInfluence::operator()(Time time) const
{
	// TODO: merge with ValueDescSkeletonLink processing

	using Skeleton = std::vector<ValueNode_Bone::Handle>;
	using Path = std::vector<BLinePoint>;

	// TODO: use generic convert function
	Path path;
	{
		auto p = (*path_)(time).get(std::vector<ValueBase>());
		std::transform(
			std::begin(p),
			std::end(p),
			std::back_inserter(path),
			[](ValueBase value) {
				return value.get(BLinePoint());
			}
		);
	}

	Skeleton skeleton;
	{
		auto p = ValueNode_StaticList::Handle::cast_dynamic(skeleton_);
		if (p)
		{
			for (int i = 0; i < p->link_count(); ++i)
			{
				auto bone_node =
				ValueNode_Bone::Handle::cast_dynamic(p->get_link(i));
				if (!bone_node.empty())
					skeleton.push_back(bone_node);
			}
		}
	}

	std::cout << "Got path with " << path.size() << " points" << std::endl;
	std::cout << "Got skeleton with " << skeleton.size() << " bones" << std::endl;

	for (auto& bline_point : path)
	{
		Skeleton affecting_bones;
		std::copy_if(
			std::begin(skeleton),
			std::end(skeleton),
			std::back_inserter(affecting_bones),
			[bline_point, time](auto bone) {
				return bone->have_influence_on(Time(0), bline_point.get_vertex());
			}
		);
		std::cout << "Got " << affecting_bones.size() << " bones" << std::endl;

		if (affecting_bones.size() == 1)
		{
			auto bone_valuenode = affecting_bones[0];
			auto bone_link = ValueNode_BoneLink::create(bline_point);
			bone_link->set_link(
				"bone",
				ValueNode_Const::create(ValueBase(bone_valuenode))
			);
			bone_link->set_link(
				"base_value",
				ValueNode_Const::create(
					ValueTransformation::back_transform(
						bone_link->get_bone_transformation(Time(0)),
						bline_point
					)
				)
			);
			bline_point = (*bone_link)(time).get(BLinePoint());
		}
		else if (affecting_bones.size() > 1)
		{
			auto average = new ValueNode_WeightedAverage(type_bline_point);
			for (auto const& bone_valuenode : affecting_bones)
			{
				auto bone_link = ValueNode_BoneLink::create(BLinePoint());
				bone_link->set_link(
					"bone",
					ValueNode_Const::create(ValueBase(bone_valuenode))
				);
				bone_link->set_link(
					"base_value",
					ValueNode_Const::create(
						ValueTransformation::back_transform(
							bone_link->get_bone_transformation(Time(0)),
							bline_point
						)
					)
				);
				auto weighted = ValueNode_Const::create(WeightedValue<BLinePoint>(1, (*bone_link)(time).get(BLinePoint())));
				average->add(weighted);
			}
			bline_point = (*average)(time).get(BLinePoint());
		}
	}

	// TODO: use convert functions
	std::vector<ValueBase> path_valuebase;
	std::transform(
		std::begin(path),
		std::end(path),
		std::back_inserter(path_valuebase),
		[](BLinePoint point) {
			return ValueBase(point);
		}
	);

	auto result = ValueBase(path_valuebase);
	result.set_loop((*path_)(time).get_loop());
	return result;
}

bool
SkeletonInfluence::check_type(Type& type)
{
	return type == type_list;
}

ValueNode::LooseHandle
SkeletonInfluence::get_link_vfunc(int i) const
{
	switch (i)
	{
		case 0: return path_;
		case 1: return skeleton_;
	}
	return nullptr;
}

bool
SkeletonInfluence::set_link_vfunc(int i, ValueNode::Handle value)
{
	switch (i)
	{
		case 0: CHECK_TYPE_AND_SET_VALUE(path_, type_list);
		case 1: CHECK_TYPE_AND_SET_VALUE(skeleton_, type_list);
	}
	return false;
}

LinkableValueNode::Vocab
SkeletonInfluence::get_children_vocab_vfunc() const
{
	auto vocab = LinkableValueNode::Vocab();
	vocab.push_back(ParamDesc(ValueBase(), "path"));
	vocab.push_back(ParamDesc(ValueBase(), "skeleton"));
	return vocab;
}

} // END of namespace valuenodes
} // END of namespace synfig

﻿#include "ModelInterface/ModelBasicBuilderFacade.h"

#include "Base/ServiceLocator.h"
#include "ModelInterface/SimulationAccess.h"
#include "ModelInterface/SimulationController.h"
#include "ModelInterface/SimulationContext.h"
#include "ModelInterface/SpaceProperties.h"

#include "VersionController.h"


VersionController::VersionController(QObject * parent) : QObject(parent)
{
	
}

void VersionController::init(SimulationContext* context)
{
	auto facade = ServiceLocator::getInstance().getService<ModelBasicBuilderFacade>();
	auto access = facade->buildSimulationAccess();
	SET_CHILD(_access, access);
	_access->init(context);
	_universeSize = context->getSpaceProperties()->getSize();
	_stack.clear();
	_snapshot.reset();

	connect(_access, &SimulationAccess::dataReadyToRetrieve, this, &VersionController::dataReadyToRetrieve);
}

bool VersionController::isStackEmpty()
{
	return _stack.empty();
}

void VersionController::clearStack()
{
	_stack.clear();
}

void VersionController::loadSimulationContentFromStack()
{
	if (_stack.empty()) {
		return;
	}
	_access->clear();
	_access->updateData(_stack.back());
	_stack.pop_back();
}

void VersionController::saveSimulationContentToStack()
{
	_target = TargetForReceivedData::Stack;
	_access->requireData({ { 0, 0 }, _universeSize }, ResolveDescription());
}

void VersionController::makeSnapshot()
{
	_target = TargetForReceivedData::Snapshot;
	_access->requireData({ { 0, 0 }, _universeSize }, ResolveDescription());
}

void VersionController::restoreSnapshot()
{
	if (!_snapshot) {
		return;
	}
	_access->clear();
	_access->updateData(*_snapshot);
}

void VersionController::dataReadyToRetrieve()
{
	if (!_target) {
		return;
	}
	if (*_target == TargetForReceivedData::Stack) {
		_stack.push_back(_access->retrieveData());
	}
	if (*_target == TargetForReceivedData::Snapshot) {
		_snapshot = _access->retrieveData();
	}
	_target.reset();
}

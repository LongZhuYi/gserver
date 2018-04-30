
local CaddTick = addTick

module("Timer", package.seeall)

local __Tick__ = __Tick__ or {}
local TICK_ID = TICK_ID or 2
local GTICK_ID = 1

function init(self)
	CaddTick(GTICK_ID, 1, 1, -1)
	self:LaddTick(self.printTT, 5, 3, self, 1, 2, 3)
end

function printTT(self, ...)
	--print("--------printTT---------", ...)
end

function tick(self, id)
	if id == 1 then 
		return
	end
	local task = __Tick__[id]
	if not task then 
		return 
	end
	task.repcnt = task.repcnt - 1
	if task.repcnt == 0 then 
		__Tick__[id] = nil
	end
	task.func(unpack(task.param))
	return 
end

function LaddTick(self, func, delay, repcnt, ...)
	TICK_ID = TICK_ID + 1
	local id = TICK_ID
	local param = {...}
	local task = {
		id = id,
		param = param,
		func = func,
		repcnt = repcnt,
	}
	__Tick__[id] = task
	CaddTick(id, delay, delay, repcnt)
end
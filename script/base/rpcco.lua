require 'common/queue'

local coyield   = coroutine.yield
local coresume  = coroutine.resume
local cocreate  = coroutine.create
local costatus  = coroutine.status
local corunning = coroutine.running

local MAX_RUNING = 1024
local MAX_COID = 1024
local COID     = 0
local rpcco = rpcco or {}
local cpool = cpool or {}
local tpool = tpool or {}
local rpool = rpool or {}

function tick()
	for cid, co in pairs(rpool) do 

	end
end

function ret(task, ...)
	--return result to other server
end

function createCo(func, ...)
	COID = COID + 1
	COID = COID % MAX_COID
	local task = {
		cid  = COID,
		func = func,
		parm = {...},
	}
	if #cpool > 0 then 
		local co = cpool[#cpool]
		table.remove(cpool, #cpool)
		return co, task
	elseif table.length(rpool) < MAX_RUNING then
		local co = cocreate(function(...)
			local func = task.func
			ret(task, func(...))
			rpool[task.cid] = nil
			while true do 
				if #tpool == 0 then 
					coyield()
				else
					local tmpTask = tpool[#tpool]
					tpool[#tpool] = nil
					local func = tmpTask.func
					ret(tmpTask, func(unpack(tmpTask.parm)))
				end
			end
		end)
		return co, task
	else
		return nil, task
	end
end

function excute(obj, func, ...)
	local co, task = createCo(func, ...)
	if co then
		rpool[task.cid] = co
		coresume(co)
	else
		table.insert(tpool, task)
	end
end





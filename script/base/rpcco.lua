--module("rpcco", package.seeall)

local coyield   = coroutine.yield
local coresume  = coroutine.resume
local cocreate  = coroutine.create
local costatus  = coroutine.status
local corunning = coroutine.running

local MAX_RUNING = 1024
local MAX_COID = 1024
local COID     = 0

local cpool = cpool or {}
local tpool = tpool or {}
local rpool = rpool or {}

rpcco = rpcco or {}

function tick()
	for cid, co in pairs(rpool) do 

	end
end

function ret(task, ...)
	--return result to other server
end

function createCo(func, ...)
	print("createCo bbb",#cpool)
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
	elseif #rpool < MAX_RUNING then
		local co = cocreate(function(...)
			local func = task.func
			func(unpack(task.parm))
			--ret(task, func(...))
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

function rpcco:excuteC(obj, func, ...)
	local co, task = createCo(func, ...)
	if co then
		rpool[task.cid] = co
		coresume(co, task)
	else
		table.insert(tpool, task)
	end
end





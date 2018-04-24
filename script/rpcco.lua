local coyield   = coroutine.yield
local coresume  = coroutine.resume
local cocreate  = coroutine.create
local costatus  = coroutine.status
local corunning = coroutine.running

local coid  = coid or 0
local rpcco = rpcco or {}
local cpool = cpool or {}
local tpool = tpool or {}
local rpool = rpool or {}

function tick()

end

function createCo()
	local co = nil
	if #cpool == 0 then 
		co = cocreate()
		coid = coid + 1
		return co, coid
	end
	co = cpool[#cpool]
	cpool[#cpool] = nil
	return co, coid
end

function excute(obj, func, ...)
	local co, coid = createCo()
	if co then
		rpool[coid] = co
		coresume(co, func, obj, ...)
	end
end





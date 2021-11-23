print("server.lua");

function OnStart()
	print("KernelService Start!");
	return InitializeSingleton();
end

OnStart();
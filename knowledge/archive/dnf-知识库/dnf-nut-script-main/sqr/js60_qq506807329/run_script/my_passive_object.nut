

function onGetMyPassiveObject_My(obj, objIndex, skillIndex, num) {
	local count = obj.getMyPassiveObjectCount(objIndex);
	for (local i = 0; i < count; i++) {
		local Object = obj.getMyPassiveObject(objIndex, i);
		if (!Object) continue;
		if (Object.getVar("skill").get_vector(0) == skillIndex) {
			if (num) {
				if (num == Object.getVar("subType").get_vector(0))
					return Object;
			} else {
				return Object;
			}
		}
	}
	return null;
}

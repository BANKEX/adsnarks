const flatten_list = (l) => {
    return [].concat.apply([], l);
};

exports.flatten_vk = (vk) => {
    return [
        flatten_list([
            vk.alpha[0], vk.alpha[1],
            flatten_list(vk.beta),
            flatten_list(vk.gamma),
            flatten_list(vk.delta),
        ]),
        flatten_list(vk.gammaABC)
    ];
};
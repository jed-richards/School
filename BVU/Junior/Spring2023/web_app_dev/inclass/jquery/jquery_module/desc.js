// desc.setup

let desc = (function() {

    // this is private
    let showValue = function() {
        let valueElm = $(this).siblings()[0];
        if ($(valueElm).is(':visible')) {
            $(valueElm).slideUp(1000);
        }
        else {
            $(valueElm).slideDown(1000);
        }
    }

    let setup = function() {
        $('.desc-name').click( showValue );
    };

    // Return setup as a publicly available function
    return { setup: setup };
})();

//let showValue = function() {
//    let valueElm = $(this).siblings()[0];
//    if ($(valueElm).is(':visible')) {
//        $(valueElm).slideUp(1000);
//    }
//    else {
//        $(valueElm).slideDown(1000);
//    }
//}
//
//let desc = {};
//
//desc['setup'] = function() {
//    $('.desc-name').click( showValue );
//};
//
//let main = (function() {
//    return desc;
//})();


var explorer = navigator.userAgent;
$(function () {
    $('input').iCheck({
        checkboxClass: 'icheckbox_square-blue',
        radioClass: 'iradio_square-blue',
        increaseArea: '20%' // optional
    });
    $('.iehref-dialog-btn').click(function () {
        $('.iehref-mask').hide()
    })
})
function checkForm(form) {
    form.password.value = $.md5("axy_" + form.password.value);
    return true;
}
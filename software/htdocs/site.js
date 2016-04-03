$(document).ready(function() {
  $('#content').attr('data', '/control.html');
  $('.navbar a').click(function (e) {
    $('#content').attr('data', $(this).data('url'));
    $('.navbar li').removeClass('active');
    $(this).parent().addClass('active');
  });
});

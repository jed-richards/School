// Creates and resets create post form
function resetSubmission() {
  $('input.form-control').val('');
  $('#post-btn').prop('disabled', false);
}


// Creates a post using /api/posts/ route
function sendPost() {
    let form = $('#post-form')[0];
    let data = new FormData(form);
    $('#post-btn').prop('disabled', true);

    $.ajax({
        type: 'POST',
        enctype: 'multipart/form-data',
        url: '/api/posts/',
        data: data,
        processData: false,
        contentType: false,
        success: function () {
          resetSubmission();
        },
        error: function() {
          $('#post-btn').prop('disabled', false);
        }
    });
}


// This is like document.ready(). It happens when the page is loaded.
$(function() {

  // Construct a click listener on the create post button
  $('#post-btn').click(function(event) {
    event.preventDefault();
    sendPost();
  });

});

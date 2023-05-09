function getProfileID() {
  return $('#profile_div').attr('profile_id');
}

function getActiveProfileID() {
  return $('#profile_div').attr('active_profile_id');
}


// Ajax function to register a like on a specific post
function like(postid) {
  $.ajax('/api/posts/' + postid + '/like/', {
    method: 'POST',
    dataType: 'json',
    success: function() {
      reloadPosts();
    },
    error: function() {
      console.log('Failed to like post');
    }
  });
}


// Ajax function to deregister a like on a specific post
function unlike(postid) {
  $.ajax('/api/posts/' + postid + '/unlike/', {
    method: 'POST',
    dataType: 'json',
    success: function() {
      reloadPosts();
    },
    error: function() {
      console.log('Failed to unlike post');
    }
  });
}


// Clears html of modal popup so we can redisplay it
function clearProfiles(post_id) {
  let postModalContent = $('.modal-body[postid=' + post_id +']');
  postModalContent.html('');
}


// Inserts a profile into the modal pupup to display
function insertProfile(profile, post_id) {
  let postModalContent = $('.modal-body[postid=' + post_id +']');
  let html = '<p class="profiles-liked">' + profile.username + '</p>';
  postModalContent.prepend(html);
}


// Ajax function to get profiles that have liked a specific post
function getLikedBy(post_id) {
  $.ajax('/api/posts/' + post_id + '/likes/', {
    method: 'GET',
    datatype: 'json',

    success: function(profiles) {
      clearProfiles(post_id);
      profiles.forEach(function(profile) {
        insertProfile(profile, post_id);
      });
    },
    error: function() {
      console.log("Error inserting profiles.")
    }
  });
}


// Inserts a post into the posts div and constructs Like/Unlike links that are 
// hidden or shown based on if the active profile has liked the post before.
// Additionally, this adds the profiles that have liked the post to the post's
// modal popup
function insertPost(post, profile_id, active_profile_id) {
  let postsDiv = $('#posts');

  let html = '' +
    '<div class="post" postid="' + post.id + '" profile_id="' + post.profile.id + '">' +
      '<a href="#" class="user-link">' + post.profile.username + '</a><br>' +
      '<p class="post-content">' + post.content + '</p><br>' + 
      '<a href="#" class="like-link" postid="' + post.id + '">Like</a>' +
      '<a href="#" class="unlike-link" postid="' + post.id + '">Unlike</a> | ' +

      '<a href"#" class="likes-link" data-bs-toggle="modal" data-bs-target="#modal-popup">' +
        '(' + post.numLikes + ')' +
      '</a>' +
      '<div class="modal fade" id="modal-popup" tabindex="-1" aria-labelledby="modalLabel" aria-hidden="true">' +
        '<div class="modal-dialog">' +
          '<div class="modal-content">' +
            '<div class="modal-header">' +
              '<h5 class="modal-title" id="modalLabel">Liked By</h5>' +
              '<button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>' +
            '</div>' +
            '<div class="modal-body" postid="' + post.id + '">' +
            '</div>' +
            '<div class="modal-footer">' +
              '<button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>' +
            '</div>' +
          '</div>' +
        '</div>' +
      '</div>' +
    '</div>';

  postsDiv.prepend(html);

  if (post.likedBy.includes(parseInt(active_profile_id))){
    $('.like-link[postid=' + post.id +']').hide()
  }
  else {
    $('.unlike-link[postid=' + post.id +']').hide()
  }

  $('.like-link[postid=' + post.id +']').click(function(event) {
    event.preventDefault();
    like(post.id);
  });

  $('.unlike-link[postid=' + post.id +']').click(function(event) {
    event.preventDefault();
    unlike(post.id);
  });

  // Add profiles to the posts modal popup
  getLikedBy(post.id);
}


// This clears the posts html so we can redisplay them 
function clearPosts() {
  let postsDiv = $('#posts');
  postsDiv.html('');
}


// This gets all posts based on the profile id.
function getPosts(profile_id, active_profile_id) {
  $.ajax('/api/posts/?profile_id=' + profile_id, {
    method: 'GET',
    datatype: 'json',

    success: function(posts) {
      clearPosts();
      posts.forEach(function(post) {
        insertPost(post, profile_id, active_profile_id);
      });
    },
    error: function() {
      $('#posts').html('cannot load posts at this time.');
    }
  });
}


// This reloads the posts so they can be updated
function reloadPosts() {
  let profile_id = getProfileID();
  let active_profile_id = getActiveProfileID();
  window.setTimeout(getPosts, 0, profile_id, active_profile_id);
}


// This is like document.ready().
$(function() {
  let profile_id = getProfileID();
  let active_profile_id = getActiveProfileID();
  getPosts(profile_id, active_profile_id);
});

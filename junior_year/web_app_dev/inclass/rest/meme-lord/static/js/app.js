
function insertPost(post) {
    let domTarget = $('#posts');
    let html = '<div class="post" postid="' + post.id + '"><h1>' +
                post.title;
    html += '</h1><img src="/static/img/uploads/' +
                post.imagepath + '"><p>Votes: ' + 
                '<span class="votescount">' + post.votes + '</span></p>' +
                '<button postid="' + post.id + '" class="upvote">upvote</button> / ' + 
                '<button postid="' + post.id + '" class="downvote">downvote</button>';
    domTarget.append(html);

    $('.upvote[postid=' + post.id + ']').click(function(event) {
        event.preventDefault();
        vote(post.id, +1);
    });

    $('.downvote[postid=' + post.id + ']').click(function(event) {
        event.preventDefault();
        vote(post.id, -1);
    });
}

function vote(postid, change) {
    let whichway = '/upvote/';
    if (change == -1) {
        whichway = '/downvote/';
    }

    $.ajax('/api/posts/' + postid + whichway, {
        method: 'POST',
        dataType: 'json',

        success: function(post) {
            let countElm = $('div.post[postid=' + post.id + ']').find('.votescount');
            countElm.html(post.votes);
        },

        error: function() {
            console.log('I have been disenfranchised!!!!!');
        }
    });
}

function clearPosts() {
    let domTarget = $('#posts');
    domTarget.html('');
}

function getAllPosts() {
    $.ajax('/api/posts', {
        method: 'GET',
        dataType: 'json',

        success: function(posts) {
            clearPosts();
            posts.forEach(function(post) {
                insertPost(post);
            });
        },

        error: function() {
            $('#posts').html('Cannot load posts at this time.');
        }
    });
}

function reloadPosts() {
    $('#posts').html('Reloading...');
    window.setTimeout(getAllPosts, 2000);
}

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
        success: reloadPosts,
        error: function() {
            $('#posts').html('Cannot post. Try again later.');
            $('#post-btn').prop('disabled', false);
        }
    });
}


// This is like document.ready().
$(function() {
    $('#reload-btn').click(function() {
        reloadPosts();
    });

    $('#post-btn').click(function(event) {
        event.preventDefault();
        sendPost();
    });


    getAllPosts();
});

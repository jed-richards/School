// Programmers: Jed Richards, Jason Konz, and Alex Chadzynski
// Date: 3/23/2023
// Description:
//   This is a jquery plugin that creates a slide show based on the images 
//   within the HTML.

$.fn.imageslide = function(opts) {

    // Get all images
    let imageItems = this.find('img');
    
    // Stylize the html
    imageItems.css('cursor', 'pointer');
    imageItems.prevObject.css('display', 'inline-block');

    // Make an index that points to current image
    let index = 0;

    // Hide all images, add click functionality, and if opts apply opts
    imageItems.each(function() {
        $(this).css('display', 'none'); 
        $(this).click(function() {
            $(imageItems[index]).css('display', 'none');
            index++;
            if (index == imageItems.length)
                index = 0;
            $(imageItems[index]).css('display', 'inline-block');
        });
        if (opts) {
            $(this).css('height', opts.imageheight);
            $(this).css('width', opts.imagewidth);
        }
    });

    // Display first image
    $(imageItems[0]).css('display', 'inline-block');

    // Add prev and next buttons to front and end of "this"
    this.prepend('<button id="prev-button" style="display:inline-block;cursor:pointer">Previous</button>');
    this.append('<button id="next-button" style="display:inline-block;cursor:pointer">Next</button>');

    // Add click functionality to next button that lives within 'this'
    $(this.find('button#next-button')).click(function() {
        $(imageItems[index]).css('display', 'none');
        index++;
        if (index == imageItems.length)
            index = 0;
        $(imageItems[index]).css('display', 'inline-block');
    });

    // Add click functionality to prev button that lives within 'this'
    $(this.find('button#prev-button')).click(function() {
        $(imageItems[index]).css('display', 'none');
        index--;
        if (index == -1)
            index = imageItems.length-1;
        $(imageItems[index]).css('display', 'inline-block');
    });

    // Return reference to this so we can chain jQuery functions
    return this;
};

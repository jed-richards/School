//jqueryObj.checklist()

// Example of jQuery Plugin

$.fn.checklist = function() {
    this.css('list-style-type', 'none');

    let litems = this.find('li');

    litems.each(function() {
        // Prepend a checkbox onto each li.
        $(this).prepend('<input type="checkbox">');
        $(this).data('checked', 'false');

        // Same as above (chaining)
        //$(this).prepend('<input type="checkbox">').data('checked', 'false');
    });

    litems.click(function() {
        if ($(this).data('checked') == 'true') {
            // Uncheck it.
            $(this).data('checked', 'false');
            $(this).find('input').removeAttr('checked');
            $(this).css('text-decoration', 'none');
        }
        else {
            // Check it.
            $(this).data('checked', 'true');
            $(this).find('input').attr('checked', 'checked');
            $(this).css('text-decoration', 'line-through');
        }
    });

    litems.css('cursor', 'pointer');

    // Return reference to this so we can chain jQuery functions
    return this;
};


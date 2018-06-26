mirror.init();
//mirror.redirectConsoleToPopup();
mirror.listen(Mirror.Events.SENSORS, {
    onchanged: function(ev) {

        var numActive = 0;

        Object.keys(ev.items).forEach(key => {
            if(ev.items[key].active) {
                $('#'+key).show();
                numActive++;
            } else {
                $('#'+key).hide();
            }
        });

        if (numActive == 1){
            Object.keys(ev.items).forEach(key => {
                $('#'+key).css("max-width","100%");
                $('#'+key).css("max-height","100%");
            });
        } else {
            Object.keys(ev.items).forEach(key => {
                $('#'+key).css("max-width","50%");
                $('#'+key).css("max-height","50%");
            });
        }
    }
});
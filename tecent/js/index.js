window.addEventListener("load", function () {
    // 添加关注的城市
    var i = 0
    var jsonData = []
    var ol = document.querySelector('ol');
    var add = document.querySelector('.add');
    add.addEventListener('click', function () {

        addCity()
    })
    function addCity() {
        var city = document.querySelector('.location p')
        console.log(city.innerHTML.split('&nbsp;')[2]);
        if (city.innerHTML.split('&nbsp;')[2] in jsonData) { }
        else {
            jsonData.push(city.innerHTML.split('&nbsp;')[2])
        }
        localStorage.setItem('city', jsonData)
        ol.innerHTML += ` <li class="item">
       <p class="city">${jsonData[i]}</p>
       <div class="weather">
           <img src="image/cloud.png" alt="">
           <p class="weathernow">多云</p>
       </div>
       <p class="temp">25°</p>
       <a href="javascript:;" class="del"></a>
   </li>`
        i++;
    }
    // 搜索
    var search = document.querySelector('#search');
    search.onfocus = function () {
        if (this.value === '搜索市、区、县等') {
            this.value = '';
        }
    };
    search.onblur = function () {
        if (this.value === '') {
            this.value = '搜索市、区、县等';
        }
    }

    // 实时天气
    var btn_prev = document.querySelector("#btn-prev");
    var btn_next = document.querySelector("#btn-next");
    var weather = document.querySelector('#weather');
    btn_prev.addEventListener('click', function () {
        if (weather.style.left !== 25) {
            animate(weather, 25);
        }
    });
    btn_next.addEventListener('click', function () {

        animate(weather, -1000);
    });

    //生活指数
    var btn_prev1 = document.querySelector("#btn-prev1");
    var btn_next1 = document.querySelector("#btn-next1");
    var content = document.querySelector('#content');
    btn_prev1.addEventListener('click', function () {
        if (content.style.left !== 0) {
            animate(content, 0);
        }
    });
    btn_next1.addEventListener('click', function () {

        animate(content, -640);
    });
    // 天气更新
    var sixdayHighTemperature = [];
    var sixdayLowTemperature = [];
    getWeather('101110101')
    function getWeather(cityCode) {
        myAxios({
            url: 'https://api.qweather.com/v7/weather/now',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: cityCode
            }

        }).then(result => {
            // console.log(result);
            const wObj = result.now;
            const nowWStr = `  <p id="wd">${wObj.temp}</p>
            <p id="tq">${wObj.text}</p>`
            document.querySelector('.report').innerHTML = nowWStr;
            const otherStr = ` 
            <p class="item">
                <i class="icon wind" id="ico-wind"></i>
                <span>${wObj.windDir}&nbsp;${wObj.windScale}级</span>
            </p>
            <p class="item">
                <i class="icon humidity" id="ico-humidity"></i>
                <span>湿度&nbsp;${wObj.humidity}%</span>
            </p>
            <p class="item">
                <i class="icon kPa" id="ico-kPa"></i>
                <span>气压&nbsp;${wObj.pressure}hPa</span>
            </p>`
            document.querySelector('#other').innerHTML = otherStr;
            const ico = ` <img class="icon" src="icon/${wObj.icon}.svg" alt="QWeather Icons">`
            document.querySelector('#current-weather').innerHTML = ico;
        })
        myAxios({
            url: 'https://api.qweather.com/v7/air/now',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: cityCode
            }
        }).then(result => {
            console.log(result);
            const qualityObj = result.now
            const qualityStr = `<p id="aqi">${qualityObj.pm2p5}&nbsp;${qualityObj.category}</p>`
            document.querySelector('.report').innerHTML += qualityStr;
            let quality = document.querySelector('#aqi')
            if (qualityObj.pm2p5 < 50) {
                quality.style.backgroundColor = '#43ce17'
            } else if (qualityObj.pm2p5 >= 50 && qualityObj.pm2p5 < 100) {
                quality.style.backgroundColor = '#efdc31'
            } else if (qualityObj.pm2p5 > 100 && qualityObj.pm2p5 <= 150) {
                quality.style.backgroundColor = '#ffaa00'
            } else if (qualityObj.pm2p5 > 150 && qualityObj.pm2p5 <= 200) {
                quality.style.backgroundColor = '#ff401a'
            } else if (qualityObj.pm2p5 > 200 && qualityObj.pm2p5 <= 300) {
                quality.style.backgroundColor = '#d20040'
            } else if (qualityObj.pm2p5 > 300) {
                quality.style.backgroundColor = '#d20040'
            }
        })
        myAxios({
            url: 'https://api.qweather.com/v7/weather/24h',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: cityCode
            }
        }).then(result => {
            // console.log(result);
            const nowObj = result.hourly;
            const nowWeater = nowObj.map(item => {
                let time = item.fxTime.slice(11, 16)
                return `<li id="item">
                <p class="txt-time">${time}</p>
                <img src="icon/${item.icon}.svg" alt="${item.text}" title="${item.text}" class="icon">
                <p class="txt-degree">${item.temp}°</p>
            </li>`
            }).join('')
            // console.log(nowWeater);
            document.querySelector('#hours #weather ol').innerHTML = nowWeater
        })
        myAxios({
            url: 'https://api.qweather.com/v7/weather/7d',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: cityCode
            }
        }).then(result => {
            // console.log(result);
            const dayForecast = result.daily
            const dayForecastStr = dayForecast.map(item => {
                var dt = new Date(item.fxDate);
                var weekDay = ["周日", "周一", "周二", "周三", "周四", "周五", "周六"];
                let week = weekDay[dt.getDay()]
                let day = item.fxDate.slice(5, 7) + '月' + item.fxDate.slice(8) + '日'
                sixdayHighTemperature.push(item.tempMax);
                sixdayLowTemperature.push(item.tempMin);
                // console.log(sixdayHighTemperature);
                return `<li class="item">
                <p class="day">${week}</p>
                <p class="data">${day}</p>
                <div class="dy-time">
                    <div class="weather">${item.textDay}</div>
                    <img src="icon/${item.iconDay}.svg" alt="${item.textDay}" title="${item.textDay}" class="icon">
                </div>
                <div class="dy-night">
                    <img src="icon/${item.iconNight}.svg" alt="${item.textNight}" title="${item.textNight}" class="icon">
                    <div class="weather">${item.textNight}</div>
                    <p class="wind">${item.windDirDay} ${item.windSpeedDay}级</p>
                </div>
            </li>`
            }).join('')
            // console.log(dayForecastStr);
            document.querySelector('.weather-day').innerHTML = dayForecastStr
            getCharts(sixdayHighTemperature, sixdayLowTemperature)
        })
        myAxios({
            url: 'https://api.qweather.com/v7/indices/1d',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: cityCode,
                type: '3,5,9,2,1,16,4,6,15,10,8,14'
            }
        }).then(result => {
            // console.log(result);
            let page = result.daily
            let pageStr = page.map(item => {
                return `<li class="item ">
                <div class="sub">
                    <i class="icon icon_${item.type}"></i>
                    <p class="content">${item.name} ${item.category}</p>
                </div>
                <div class="ct-detail">
                    <div class="detail">
                        <p></p>
                        <p>${item.text}</p>
                    </div>
                </div>
            </li>`
            }).join('')
            document.querySelector('#living1').innerHTML = pageStr
        })
        myAxios({
            url: 'https://api.qweather.com/v7/indices/1d',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: cityCode,
                type: '4,6,15,10,8,14'
            }
        }).then(result => {
            // console.log(result);
            let page = result.daily
            let pageStr1 = page.map(item => {
                return `<li class="item ">
                <div class="sub">
                    <i class="icon icon_${item.type}"></i>
                    <p class="content">${item.name} ${item.category}</p>
                </div>
                <div class="ct-detail">
                    <div class="detail">
                        <p></p>
                        <p>${item.text}</p>
                    </div>
                </div>
            </li>`
            }).join('')
            document.querySelector('#living2').innerHTML = pageStr1
        })
    }



    document.querySelector('#search').addEventListener('input', function (e) {
        console.log(e.target.value);
        myAxios({
            url: 'https://geoapi.qweather.com/v2/city/lookup',
            params: {
                key: '646cee89ebde47ce8f63ba82effa5a5c',
                location: e.target.value
            }
        }).then(result => {
            // console.log(result);
            const location = result.location
            const locationStr = location.map(item => {
                return `<li class="city-item" data-id="${item.id}">${item.adm1}-${item.adm2}-${item.name}</li>`
            }).join('')
            document.querySelector('.search-list').innerHTML = locationStr
        })
    })
    document.querySelector('.search-list').addEventListener('click', function (e) {
        if (e.target.classList.contains('city-item')) {
            const cityCode = e.target.dataset.id
            console.log(cityCode);
            myAxios({
                url: 'https://geoapi.qweather.com/v2/city/lookup',
                params: {
                    key: '646cee89ebde47ce8f63ba82effa5a5c',
                    location: cityCode
                }
            }).then(result => {
                console.log(result);
                const locate = result.location
                const locateStr = locate.map(item => {
                    return `<p data-id='${result.location[0].id}'><img src="image/dw.png" alt="">&nbsp;${item.adm1}&nbsp;${item.adm2}市</p>
                    <div class="care">
                    <span class="c-head">关注的城市</span>
                    <ol class="care-list">
                        <li class="item">
                            <p class="city">西安市</p>
                            <div class="weather">
                                <img src="image/cloud.png" alt="">
                                <p class="weathernow">多云</p>
                            </div>
                            <p class="temp">25°</p>
                            <a href="javascript:;" class="del"></a>
                        </li>
                    </ol>
                </div>`
                })
                document.querySelector('.location').innerHTML = locateStr
            })
            getWeather(cityCode)
        }
    })

    function getCharts(sixdayHighTemperature, sixdayLowTemperature) {
        var canvas = document.getElementById("myCanvas");
        var ctx = canvas.getContext("2d");
        var picHeight = 140;
        var maxHighTemp = maxNum(sixdayHighTemperature);
        var minLowTemp = minNum(sixdayLowTemperature);
        var maxRange = maxHighTemp - minLowTemp;
        // console.log(sixdayHighTemperature);
        function maxNum(arr) {
            var maxNum = 0;
            if (arr.length) {
                for (var i = 0, len = arr.length; i < len; i++) {
                    if (i == 0) {
                        maxNum = arr[0];
                    } else if (maxNum < arr[i]) {
                        maxNum = arr[i];
                    }
                }
            }
            return maxNum;
        }
        function minNum(arr) {
            var minNum = 0;
            if (arr.length) {
                for (var i = 0, len = arr.length; i < len; i++) {
                    if (i == 0) {
                        minNum = arr[0];
                    } else if (minNum > arr[i]) {
                        minNum = arr[i];
                    }
                }
            }
            return minNum;
        }
        ctx.lineWidth = 5;
        (function drawHighTemp(temps) {
            ctx.beginPath();
            ctx.strokeStyle = "#fcc471";
            var drawX = 0,
                drawY = 0;
            var distance = Math.floor(picHeight / maxRange);
            for (var i = 0, len = temps.length; i < len; i++) {
                drawX = i * 120 + 100;
                drawY = (maxHighTemp - temps[i]) * distance + 25;
                if (i == 0) {
                    ctx.moveTo(drawX, drawY);
                } else {
                    ctx.lineTo(drawX, drawY);
                }
            }
            ctx.stroke();
            ctx.closePath();

            ctx.beginPath();
            ctx.fillStyle = "#fcc471";
            var drawX = 0,
                drawY = 0;
            var distance = Math.floor(picHeight / maxRange);
            for (var i = 0, len = temps.length; i < len; i++) {
                drawX = i * 120 + 100;
                drawY = (maxHighTemp - temps[i]) * distance + 25;
                ctx.arc(drawX, drawY, 5, 0, 2 * Math.PI, false);
                ctx.fill();
                ctx.font = '20px Microsoft YaHei'
                ctx.fillText(temps[i], drawX - 10, drawY - 10)
                ctx.closePath();
            }
        })(sixdayHighTemperature);

        (function drawHighTemp(temps) {
            ctx.strokeStyle = "#94ccf9";
            ctx.beginPath();
            var drawX = 0,
                drawY = 0;
            var distance = Math.floor(picHeight / maxRange);
            for (var i = 0, len = temps.length; i < len; i++) {
                drawX = i * 120 + 100;
                drawY = picHeight - (temps[i] - minLowTemp) * distance - 25;
                if (i == 0) {
                    ctx.moveTo(drawX, drawY);
                } else {
                    ctx.lineTo(drawX, drawY);
                }
            }
            ctx.stroke();
            ctx.closePath();

            ctx.beginPath();
            ctx.fillStyle = "#94ccf9";
            var drawX = 0,
                drawY = 0;
            var distance = Math.floor(picHeight / maxRange);
            for (var i = 0, len = temps.length; i < len; i++) {
                drawX = i * 120 + 100;
                drawY = picHeight - (temps[i] - minLowTemp) * distance - 25;
                ctx.arc(drawX, drawY, 5, 0, 2 * Math.PI, false);
                ctx.fill();
                ctx.font = '20px Microsoft YaHei'
                ctx.fillText(temps[i], drawX - 10, drawY + 30)
                ctx.closePath();
            }
        })(sixdayLowTemperature);
    }

})
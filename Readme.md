<!DOCTYPE html><html><head><meta charset="utf-8"><title>HTTP Restful API Server Example using React.md</title><style></style></head><body id="preview">
<h1 class="code-line" data-line-start=0 data-line-end=1 ><a id="HTTP_Restful_API_Server_Example_using_React_0"></a>HTTP Restful API Server Example using React</h1>
<p class="has-line-data" data-line-start="2" data-line-end="3">This project demonstrates how to run a React application on an ESP32 microcontroller using ESP-IDF as the IoT development framework and React with TypeScript for the frontend. Additionally, QEMU (Quick Emulator) has been utilized to run ESP32 code without the need for physical hardware.</p>
<h2 class="code-line" data-line-start=4 data-line-end=5 ><a id="Overview_4"></a>Overview</h2>
<p class="has-line-data" data-line-start="6" data-line-end="7">This example is an adaptation of the <a href="https://github.com/espressif/esp-idf/blob/master/examples/protocols/http_server/restful_server/README.md">RESTful server example</a> (originally built using the Vue framework) from the official ESP-IDF GitHub repository. In this version, I’ve used the popular React framework to achieve the similar functionality.</p>
<h2 class="code-line" data-line-start=8 data-line-end=9 ><a id="Deploy_Mode_Types_8"></a>Deploy Mode Types</h2>
<ul>
<li class="has-line-data" data-line-start="9" data-line-end="10">SPI Flash</li>
<li class="has-line-data" data-line-start="10" data-line-end="11">SD Card</li>
<li class="has-line-data" data-line-start="11" data-line-end="13">Semihost Technology</li>
</ul>
<p class="has-line-data" data-line-start="13" data-line-end="14">Note: Only SD Card mode is supported when using QEMU.</p>
<h2 class="code-line" data-line-start=15 data-line-end=16 ><a id="Software_Requirements_15"></a>Software Requirements</h2>
<ul>
<li class="has-line-data" data-line-start="18" data-line-end="19">[node v23 or later]</li>
<li class="has-line-data" data-line-start="19" data-line-end="20">[ESP-IDF]</li>
<li class="has-line-data" data-line-start="20" data-line-end="22">[Docker]: Required only when using QEMU</li>
</ul>
<h2 class="code-line" data-line-start=22 data-line-end=23 ><a id="How_to_use_example_22"></a>How to use example</h2>
<p class="has-line-data" data-line-start="24" data-line-end="25">If SD Card is used to deploy the website, adjust the pin connections shown below according to your setup:</p>
<table class="table table-striped table-bordered">
<thead>
<tr>
<th>ESP32</th>
<th>SD Card</th>
</tr>
</thead>
<tbody>
<tr>
<td>GPIO2</td>
<td>D0</td>
</tr>
<tr>
<td>GPIO4</td>
<td>D1</td>
</tr>
<tr>
<td>GPIO12</td>
<td>D2</td>
</tr>
<tr>
<td>GPIO13</td>
<td>D3</td>
</tr>
<tr>
<td>GPIO14</td>
<td>CLK</td>
</tr>
<tr>
<td>GPIO15</td>
<td>CMD</td>
</tr>
</tbody>
</table>
<p class="has-line-data" data-line-start="35" data-line-end="36">Note: Optional when using QEMU.</p>
<p class="has-line-data" data-line-start="37" data-line-end="38"><strong>Project Configuration</strong></p>
<ul>
<li class="has-line-data" data-line-start="38" data-line-end="39">If you are not using QEMU and want to use Wi-Fi for coonectivity, then open the project configuration menu and navigate to “WiFi Configuration” option and set your WiFi SSID and Password.</li>
<li class="has-line-data" data-line-start="39" data-line-end="41">Ethernet support is available in QEMU for ESP-IDF as described <a href="https://github.com/espressif/esp-toolchain-docs/blob/main/qemu/esp32/README.md">here</a>.</li>
</ul>
<p class="has-line-data" data-line-start="41" data-line-end="42">To build the react application, do the following.</p>
<pre><code class="has-line-data" data-line-start="44" data-line-end="48" class="language-sh"><span class="hljs-built_in">cd</span> path_to_this_example/front/web-demo
npm i
npm run build
</code></pre>
<p class="has-line-data" data-line-start="48" data-line-end="49">Note: This should generate a folder named “dist” inside the web-demo directory.</p>
<p class="has-line-data" data-line-start="50" data-line-end="51"><strong>For only those using QEMU</strong></p>
<p class="has-line-data" data-line-start="52" data-line-end="53">To add SD card to the setup; create an image of the SD Card and pass it to the QEMU later.</p>
<pre><code class="has-line-data" data-line-start="54" data-line-end="63" class="language-sh">dd <span class="hljs-keyword">if</span>=/dev/zero bs=$((<span class="hljs-number">1024</span>*<span class="hljs-number">1024</span>)) count=<span class="hljs-number">64</span> of=sd_image.bin  //create <span class="hljs-number">64</span>MB raw image file
mkfs.vfat sd_image.bin                      //Format the SD card image
mkdir /MOUNT_POINT                          //Mount the SD card image
mount -o loop sd_image.bin /MOUNT_POINT     //Mount the SD card image
cp abc.txt /MOUNT_POINT                     //copy files to mount point
cp -r abc /MOUNT_POINT                      //or instead copy directory
ls /MOUNT_POINT                             //verify the mount
umount /MOUNT_POINT                         //unmount the image
</code></pre>
<p class="has-line-data" data-line-start="64" data-line-end="65">To generate a merged bin file, with the name result.bin in this case, run the command given below. Change the offset for bootloader, partition table, and firmware bin file, if needed.</p>
<pre><code class="has-line-data" data-line-start="67" data-line-end="69" class="language-sh">python -m esptool --chip esp32 merge_bin --output result.bin --fill-flash-size <span class="hljs-number">4</span>MB <span class="hljs-number">0</span>x1000 build/bootloader/bootloader.bin <span class="hljs-number">0</span>x8000 build/partition_table/partition-table.bin <span class="hljs-number">0</span>x10000 build/{YOUR_PROJECT_NAME}.bin --flash_mode dio --flash_freq <span class="hljs-number">40</span>m --flash_size <span class="hljs-number">4</span>MB
</code></pre>
<p class="has-line-data" data-line-start="69" data-line-end="70">Pass the SD Card image to the QEMU and forward the connection to the port 8000 on your local machine.</p>
<pre><code class="has-line-data" data-line-start="72" data-line-end="74" class="language-sh">qemu-system-xtensa -nographic -machine esp32 -drive file=result.bin,<span class="hljs-keyword">if</span>=mtd,format=raw -nic user,model=open_eth,id=lo0,hostfwd=tcp:<span class="hljs-number">127.0</span>.<span class="hljs-number">0.1</span>:<span class="hljs-number">8000</span>-:<span class="hljs-number">80</span> -drive file=sd_image.bin,<span class="hljs-keyword">if</span>=sd,format=raw
</code></pre>

</body></html>

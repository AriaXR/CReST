# CR User Study Toolkit
This project was developed in the Oculus distribution of Unreal Engine 4.27, which can be found here: https://github.com/Oculus-VR/UnrealEngine/tree/4.27
The CReST plugin is located in "CReST_Template/Plugins/CReST", this folder can be copied to your own project to import the plugin.
The implementation of the case study is located "VReplica", as an example of how we applied to plugin to the case study from the paper (https://aria.cs.kuleuven.be/papers/Cools_MUM2023.pdf)

# CReST setup instructions
1. Import CReST plugin
2. Create child CReST_Controller
    1. Implement the HandleServerVEUpdate event
    2. First switch on the type of update: load, start, finished, pause
    3. “Condition” is the name entered in the conditions matrix, or the name of the step in case of a pre- or post-study step
3. Create child GameMode
    1. set VR Pawn of project as Default Pawn Class
    2. input study procedure under “Study Procedure”
    3. set newly created CReST Controller
4. Building for Quest Pro
    1. +ExtraPermissions=android.permission.INTERNET
    +ExtraPermissions=android.permission.ACCESS_NETWORK_STATE
    2. add “Meta Quest Pro” under “Package for Meta Quest devices”
5. Add ip address of host pc to “ip_address.txt” file under This PC\Quest Pro\Internal shared storage\UE4Game\CReST_Template

# Author contact information
Researchers that have an interest in using this project can always contact us on robbe.cools@kuleuven.be
